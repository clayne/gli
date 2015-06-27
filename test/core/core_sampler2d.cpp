//////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2015 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file gli/core/texture_2d.cpp
/// @date 2011-10-11 / 2013-11-25
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#include <gli/gli.hpp>
#include <ctime>

namespace gli{
namespace detail
{
	template <typename genType>
	genType textureLodLinear(genType const * const TexelData, texture2D::dim_type const & TexelDim, texture2D::texcoord_type const & Texcoord)
	{
		std::size_t const s_below = std::size_t(glm::floor(Texcoord.s * float(TexelDim.x - 1)));
		std::size_t const s_above = std::size_t(glm::ceil( Texcoord.s * float(TexelDim.x - 1)));
		std::size_t const t_below = std::size_t(glm::floor(Texcoord.t * float(TexelDim.y - 1)));
		std::size_t const t_above = std::size_t(glm::ceil( Texcoord.t * float(TexelDim.y - 1)));

		float const s_step = 1.0f / float(TexelDim.x);
		float const t_step = 1.0f / float(TexelDim.y);

		float const s_below_normalized = s_below / float(TexelDim.x);
		float const s_above_normalized = s_above / float(TexelDim.x);
		float const t_below_normalized = t_below / float(TexelDim.y);
		float const t_above_normalized = t_above / float(TexelDim.y);

		genType const Value1 = TexelData[s_below + t_below * TexelDim.x];
		genType const Value2 = TexelData[s_above + t_below * TexelDim.x];
		genType const Value3 = TexelData[s_above + t_above * TexelDim.x];
		genType const Value4 = TexelData[s_below + t_above * TexelDim.x];

		float const BlendA = float(Texcoord.s - s_below_normalized) * float(TexelDim.x - 1);
		float const BlendB = float(Texcoord.s - s_below_normalized) * float(TexelDim.x - 1);
		float const BlendC = float(Texcoord.t - t_below_normalized) * float(TexelDim.y - 1);

		genType const ValueA(glm::mix(Value1, Value2, BlendA));
		genType const ValueB(glm::mix(Value4, Value3, BlendB));

		return genType(glm::mix(ValueA, ValueB, BlendC));
	}

	template <typename genType>
	genType textureLodNearest(genType const * const TexelData, texture2D::dim_type const & TexelDim, texture2D::texcoord_type const & Texcoord)
	{
		std::size_t const s = std::size_t(glm::floor(Texcoord.s * float(TexelDim.x - 1)));
		std::size_t const t = std::size_t(glm::floor(Texcoord.t * float(TexelDim.y - 1)));

		return TexelData[s + t * TexelDim.x];
	}
}//namespace detail

	enum wrap
	{
		WRAP_CLAMP_TO_EDGE, WRAP_FIRST = WRAP_CLAMP_TO_EDGE,
		//WRAP_CLAMP_TO_BORDER,
		WRAP_REPEAT,
		WRAP_MIRROR_REPEAT,
		WRAP_MIRROR_CLAMP_TO_EDGE, WRAP_LAST = WRAP_MIRROR_CLAMP_TO_EDGE
		//WRAP_MIRROR_CLAMP_TO_BORDER
	};

	enum
	{
		WRAP_COUNT = WRAP_LAST - WRAP_FIRST + 1
	};

	enum filter
	{
		FILTER_NEAREST, FILTER_FIRST = FILTER_NEAREST,
		FILTER_LINEAR, FILTER_LAST = FILTER_LINEAR,
	};

	enum
	{
		FILTER_COUNT = FILTER_LAST - FILTER_FIRST + 1
	};

	template <typename genType>
	class sampler
	{
		typedef float (*wrapFunc)(float const & texcoord);
		typedef genType (*textureLodFunc)(genType const * const TexelData, texture2D::dim_type const & TexelDim, texture2D::texcoord_type const & Texcoord);

	protected:
		wrapFunc getFunc(wrap WrapMode) const
		{
			static wrapFunc Table[] =
			{
				glm::clamp,
				glm::repeat,
				glm::mirrorRepeat,
				glm::mirrorClamp
			};
			static_assert(sizeof(Table) / sizeof(Table[0]) == WRAP_COUNT, "Table needs to be updated");

			return Table[WrapMode];
		}

		textureLodFunc getFunc(filter Filter) const
		{
			static textureLodFunc Table[] =
			{
				detail::textureLodNearest,
				detail::textureLodLinear
			};
			static_assert(sizeof(Table) / sizeof(Table[0]) == FILTER_COUNT, "Table needs to be updated");

			return Table[Filter];
		}

	public:
		sampler(wrap Wrap, filter Mip, filter Min)
			: WrapMode(Wrap)
			, WrapFunc(getFunc(Wrap))
			, TextureLodFunc(getFunc(Min))
			, Mip(Mip)
		{}

	protected:
		wrap WrapMode;
		wrapFunc WrapFunc;
		textureLodFunc TextureLodFunc;
		filter Mip;
	};

	template <typename genType>
	class sampler2D : public sampler<genType>
	{
		enum level
		{
			LEVEL_FIRST,
			LEVEL_LAST
		};

		enum
		{
			LEVEL_COUNT = LEVEL_LAST - LEVEL_FIRST + 1
		};

		struct cache
		{
			genType* TexelData;
			texture2D::size_type TexelSize;
			texture2D::dim_type TexelDim;
			texture2D::size_type TexelLevel;
		};

	public:
		sampler2D(texture2D const & Texture, wrap Wrap, filter Mip, filter Min/*, filter Mag, filter Min, filter Mip*/)
			: sampler<genType>(Wrap, Texture.levels() > 1 ? Mip : FILTER_NEAREST, Min)
			, Texture(Texture)
			, Level(0)
		{
			assert(!Texture.empty());
			assert(!is_compressed(Texture.format()));

			this->updateCacheLevel(0);
		}

		genType texelFetch(texture2D::dim_type const & TexelCoord, texture2D::size_type const & Level)
		{
			if(this->Levels[LEVEL_FIRST] != Level)
				this->updateCacheLevel(Level);

			std::size_t const Index = TexelCoord.x + TexelCoord.y * this->Caches[LEVEL_FIRST].TexelDim.x;
			assert(Index < this->Caches[LEVEL_FIRST].TexelSize);

			return *(this->Caches[LEVEL_FIRST].TexelData + Index);
		}

		void texelWrite(texture2D::dim_type const & TexelCoord, texture2D::size_type const & Level, genType const & Color)
		{
			if(this->Levels[LEVEL_FIRST] != Level)
				this->updateCacheLevel(Level);

			std::size_t const Index = TexelCoord.x + TexelCoord.y * this->Caches[LEVEL_FIRST].TexelDim.x;
			assert(Index < this->Caches[LEVEL_FIRST].TexelSize);

			*(this->Caches[LEVEL_FIRST].TexelData + Index) = Color;
		}

		genType textureLod(texture2D::texcoord_type const & Texcoord, float Level)
		{
			texture2D::texcoord_type const TexcoordWrap(this->WrapFunc(Texcoord.x), this->WrapFunc(Texcoord.y));

			if(this->Level != Level)
				this->updateCacheMips(Level);

			return this->TextureLodFunc(this->Caches[LEVEL_FIRST].TexelData, this->Caches[LEVEL_FIRST].TexelDim, TexcoordWrap);
		}

	private:
		void updateCacheLevel(std::size_t Level)
		{
			this->Levels[LEVEL_FIRST] = Level;
			this->Levels[LEVEL_LAST] = Level;

			this->Caches[LEVEL_FIRST].TexelData = this->Caches[LEVEL_LAST].TexelData = Texture[Level].data<genType>();
			this->Caches[LEVEL_FIRST].TexelSize = this->Caches[LEVEL_LAST].TexelSize = Texture[Level].size<genType>();
			this->Caches[LEVEL_FIRST].TexelDim = this->Caches[LEVEL_LAST].TexelDim = texture2D::dim_type(Texture[Level].dimensions());
		}

		void updateCacheMips(float Level)
		{
			this->Level = Level;

			std::size_t const LevelFirst = static_cast<std::size_t>(this->Mip == FILTER_NEAREST ? glm::round(Level) : glm::floor(Level));
			std::size_t const LevelLast = static_cast<std::size_t>(this->Mip == FILTER_NEAREST ? glm::round(Level) : glm::ceil(Level));

			this->Levels[LEVEL_FIRST] = LevelFirst;
			this->Levels[LEVEL_LAST] = LevelLast;

			this->Caches[LEVEL_FIRST].TexelData = Texture[LevelFirst].data<genType>();
			this->Caches[LEVEL_FIRST].TexelSize = Texture[LevelFirst].size<genType>();
			this->Caches[LEVEL_FIRST].TexelDim = texture2D::dim_type(Texture[LevelFirst].dimensions());

			this->Caches[LEVEL_LAST].TexelData = LevelFirst == LevelLast ? this->Caches[LEVEL_FIRST].TexelData : Texture[LevelLast].data<genType>();
			this->Caches[LEVEL_LAST].TexelSize = LevelFirst == LevelLast ? this->Caches[LEVEL_FIRST].TexelSize : Texture[LevelLast].size<genType>();
			this->Caches[LEVEL_LAST].TexelDim = LevelFirst == LevelLast ? this->Caches[LEVEL_FIRST].TexelDim : texture2D::dim_type(Texture[LevelLast].dimensions());
		}

		texture2D const & Texture;
		float Level;
		std::array<std::size_t, LEVEL_COUNT> Levels;
		std::array<cache, LEVEL_COUNT> Caches;
	};
}//namespace gli

namespace fetch
{
	int test()
	{
		int Error(0);

		gli::texture2D Texture(1, gli::FORMAT_RGBA8_UNORM, gli::texture2D::dim_type(4, 2));
		*(Texture.data<glm::u8vec4>() + 0) = glm::u8vec4(255,   0,   0, 255);
		*(Texture.data<glm::u8vec4>() + 1) = glm::u8vec4(255, 128,   0, 255);
		*(Texture.data<glm::u8vec4>() + 2) = glm::u8vec4(255, 255,   0, 255);
		*(Texture.data<glm::u8vec4>() + 3) = glm::u8vec4(128, 255,   0, 255);
		*(Texture.data<glm::u8vec4>() + 4) = glm::u8vec4(  0, 255,   0, 255);
		*(Texture.data<glm::u8vec4>() + 5) = glm::u8vec4(  0, 255, 255, 255);
		*(Texture.data<glm::u8vec4>() + 6) = glm::u8vec4(  0,   0, 255, 255);
		*(Texture.data<glm::u8vec4>() + 7) = glm::u8vec4(255,   0, 255, 255);

		glm::u8vec4 Data0 = Texture.fetch<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 0);
		glm::u8vec4 Data1 = Texture.fetch<glm::u8vec4>(gli::texture2D::dim_type(1, 0), 0);
		glm::u8vec4 Data2 = Texture.fetch<glm::u8vec4>(gli::texture2D::dim_type(2, 0), 0);
		glm::u8vec4 Data3 = Texture.fetch<glm::u8vec4>(gli::texture2D::dim_type(3, 0), 0);
		glm::u8vec4 Data4 = Texture.fetch<glm::u8vec4>(gli::texture2D::dim_type(0, 1), 0);
		glm::u8vec4 Data5 = Texture.fetch<glm::u8vec4>(gli::texture2D::dim_type(1, 1), 0);
		glm::u8vec4 Data6 = Texture.fetch<glm::u8vec4>(gli::texture2D::dim_type(2, 1), 0);
		glm::u8vec4 Data7 = Texture.fetch<glm::u8vec4>(gli::texture2D::dim_type(3, 1), 0);

		return Error;
	}
}//namespace fetch

namespace sampler
{
	int test()
	{
		int Error(0);

		gli::texture2D::dim_type const Size(512);
		gli::texture2D TextureA(1, gli::FORMAT_RGBA8_UNORM, Size);

		{
			std::clock_t TimeStart = std::clock();

			for(std::size_t y = 0; y < Size.y; ++y)
			for(std::size_t x = 0; x < Size.x; ++x)
			{
				gli::texelWrite(TextureA, gli::texture2D::dim_type(x, y), 0, glm::u8vec4(255, 128,   0, 255));
			}

			std::clock_t TimeEnd = std::clock();

			printf("texelWrite(texture2D) - Time: %d\n", TimeEnd - TimeStart);
		}

		gli::texture2D TextureB(1, gli::FORMAT_RGBA8_UNORM, Size);

		{
			gli::sampler2D<glm::u8vec4> Sampler(TextureB, gli::WRAP_CLAMP_TO_EDGE, gli::FILTER_LINEAR, gli::FILTER_LINEAR);

			{
				std::clock_t TimeStart = std::clock();

				for(std::size_t y = 0; y < Size.y; ++y)
				for(std::size_t x = 0; x < Size.x; ++x)
				{
					Sampler.texelWrite(gli::texture2D::dim_type(x, y), 0, glm::u8vec4(255, 128,   0, 255));
				}

				std::clock_t TimeEnd = std::clock();

				printf("sampler2D::texelWrite - Time: %d\n", TimeEnd - TimeStart);
			}

			{
				std::clock_t TimeStart = std::clock();

				for(float y = -0.5f; y < 1.5f; y += 0.025f)
				for(float x = -0.5f; x < 1.5f; x += 0.025f)
				{
					glm::u8vec4 Color = Sampler.textureLod(gli::texture2D::texcoord_type(x, y), 0);

					Error += glm::all(glm::equal(Color, glm::u8vec4(255, 128,   0, 255))) ? 0 : 1;
				}

				std::clock_t TimeEnd = std::clock();

				printf("sampler2D::textureLod - Time: %d\n", TimeEnd - TimeStart);
			}
		}

		Error += TextureA == TextureB ? 0 : 1;

		return Error;
	}
}//namespace sampler

int main()
{
	int Error(0);

	Error += fetch::test();
	Error += sampler::test();

	return Error;
}
