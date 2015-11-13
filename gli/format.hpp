///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2012 G-Truc Creation (www.g-truc.net)
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
/// @file gli/format.hpp
/// @date 2012-10-16 / 2015-06-16
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "type.hpp"
#include <cstdint>

namespace gli
{
	enum format
	{
		FORMAT_UNDEFINED = 0,

		FORMAT_RG4_UNORM_PACK8, FORMAT_FIRST = FORMAT_RG4_UNORM_PACK8,
		FORMAT_RGBA4_UNORM_PACK16,
		FORMAT_BGRA4_UNORM_PACK16,
		FORMAT_R5G6B5_UNORM_PACK16,
		FORMAT_B5G6R5_UNORM_PACK16,
		FORMAT_RGB5A1_UNORM_PACK16,
		FORMAT_BGR5A1_UNORM_PACK16,
		FORMAT_A1RGB5_UNORM_PACK16,

		FORMAT_R8_UNORM_PACK8,
		FORMAT_R8_SNORM_PACK8,
		FORMAT_R8_USCALED_PACK8,
		FORMAT_R8_SSCALED_PACK8,
		FORMAT_R8_UINT_PACK8,
		FORMAT_R8_SINT_PACK8,
		FORMAT_R8_SRGB_PACK8,

		FORMAT_RG8_UNORM_PACK8,
		FORMAT_RG8_SNORM_PACK8,
		FORMAT_RG8_USCALED_PACK8,
		FORMAT_RG8_SSCALED_PACK8,
		FORMAT_RG8_UINT_PACK8,
		FORMAT_RG8_SINT_PACK8,
		FORMAT_RG8_SRGB_PACK8,

		FORMAT_RGB8_UNORM_PACK8,
		FORMAT_RGB8_SNORM_PACK8,
		FORMAT_RGB8_USCALED_PACK8,
		FORMAT_RGB8_SSCALED_PACK8,
		FORMAT_RGB8_UINT_PACK8,
		FORMAT_RGB8_SINT_PACK8,
		FORMAT_RGB8_SRGB_PACK8,

		FORMAT_BGR8_UNORM_PACK8,
		FORMAT_BGR8_SNORM_PACK8,
		FORMAT_BGR8_USCALED_PACK8,
		FORMAT_BGR8_SSCALED_PACK8,
		FORMAT_BGR8_UINT_PACK8,
		FORMAT_BGR8_SINT_PACK8,
		FORMAT_BGR8_SRGB_PACK8,

		FORMAT_RGBA8_UNORM_PACK8,
		FORMAT_RGBA8_SNORM_PACK8,
		FORMAT_RGBA8_USCALED_PACK8,
		FORMAT_RGBA8_SSCALED_PACK8,
		FORMAT_RGBA8_UINT_PACK8,
		FORMAT_RGBA8_SINT_PACK8,
		FORMAT_RGBA8_SRGB_PACK8,

		FORMAT_BGRA8_UNORM_PACK8,
		FORMAT_BGRA8_SNORM_PACK8,
		FORMAT_BGRA8_USCALED_PACK8,
		FORMAT_BGRA8_SSCALED_PACK8,
		FORMAT_BGRA8_UINT_PACK8,
		FORMAT_BGRA8_SINT_PACK8,
		FORMAT_BGRA8_SRGB_PACK8,

		FORMAT_RGBA8_UNORM_PACK32,
		FORMAT_RGBA8_SNORM_PACK32,
		FORMAT_RGBA8_USCALED_PACK32,
		FORMAT_RGBA8_SSCALED_PACK32,
		FORMAT_RGBA8_UINT_PACK32,
		FORMAT_RGBA8_SINT_PACK32,
		FORMAT_RGBA8_SRGB_PACK32,

		FORMAT_RGB10A2_UNORM_PACK32,
		FORMAT_RGB10A2_SNORM_PACK32,
		FORMAT_RGB10A2_USCALED_PACK32,
		FORMAT_RGB10A2_SSCALED_PACK32,
		FORMAT_RGB10A2_UINT_PACK32,
		FORMAT_RGB10A2_SINT_PACK32,

		FORMAT_BGR10A2_UNORM_PACK32,
		FORMAT_BGR10A2_SNORM_PACK32,
		FORMAT_BGR10A2_USCALED_PACK32,
		FORMAT_BGR10A2_SSCALED_PACK32,
		FORMAT_BGR10A2_UINT_PACK32,
		FORMAT_BGR10A2_SINT_PACK32,

		FORMAT_R16_UNORM,
		FORMAT_R16_SNORM,
		FORMAT_R16_USCALED,
		FORMAT_R16_SSCALED,
		FORMAT_R16_UINT,
		FORMAT_R16_SINT,
		FORMAT_R16_SFLOAT,

		FORMAT_RG16_UNORM,
		FORMAT_RG16_SNORM,
		FORMAT_RG16_USCALED,
		FORMAT_RG16_SSCALED,
		FORMAT_RG16_UINT,
		FORMAT_RG16_SINT,
		FORMAT_RG16_SFLOAT,

		FORMAT_RGB16_UNORM,
		FORMAT_RGB16_SNORM,
		FORMAT_RGB16_USCALED,
		FORMAT_RGB16_SSCALED,
		FORMAT_RGB16_UINT,
		FORMAT_RGB16_SINT,
		FORMAT_RGB16_SFLOAT,

		FORMAT_RGBA16_UNORM,
		FORMAT_RGBA16_SNORM,
		FORMAT_RGBA16_USCALED,
		FORMAT_RGBA16_SSCALED,
		FORMAT_RGBA16_UINT,
		FORMAT_RGBA16_SINT,
		FORMAT_RGBA16_SFLOAT,

		FORMAT_R32_UINT,
		FORMAT_R32_SINT,
		FORMAT_R32_SFLOAT,

		FORMAT_RG32_UINT,
		FORMAT_RG32_SINT,
		FORMAT_RG32_SFLOAT,

		FORMAT_RGB32_UINT,
		FORMAT_RGB32_SINT,
		FORMAT_RGB32_SFLOAT,

		FORMAT_RGBA32_UINT,
		FORMAT_RGBA32_SINT,
		FORMAT_RGBA32_SFLOAT,

		FORMAT_R64_UINT,
		FORMAT_R64_SINT,
		FORMAT_R64_SFLOAT,

		FORMAT_RG64_UINT,
		FORMAT_RG64_SINT,
		FORMAT_RG64_SFLOAT,

		FORMAT_RGB64_UINT,
		FORMAT_RGB64_SINT,
		FORMAT_RGB64_SFLOAT,

		FORMAT_RGBA64_UINT,
		FORMAT_RGBA64_SINT,
		FORMAT_RGBA64_SFLOAT,

		FORMAT_RG11B10_UFLOAT_PACK32,
		FORMAT_RGB9E5_UFLOAT_PACK32,

		FORMAT_D16_UNORM,
		FORMAT_D24_UNORM_X8_UINT,
		FORMAT_D32_SFLOAT,
		FORMAT_S8_UINT,
		FORMAT_D16_UNORM_S8_UINT,
		FORMAT_D24_UNORM_S8_UINT,
		FORMAT_D32_SFLOAT_S8_UINT,

		FORMAT_RGB_DXT1_UNORM,
		FORMAT_RGB_DXT1_SRGB,
		FORMAT_RGBA_DXT1_UNORM,
		FORMAT_RGBA_DXT1_SRGB,
		FORMAT_RGBA_DXT3_UNORM,
		FORMAT_RGBA_DXT3_SRGB,
		FORMAT_RGBA_DXT5_UNORM,
		FORMAT_RGBA_DXT5_SRGB,
		FORMAT_R_ATI1N_UNORM,
		FORMAT_R_ATI1N_SNORM,
		FORMAT_RG_ATI2N_UNORM,
		FORMAT_RG_ATI2N_SNORM,
		FORMAT_RGB_BP_UFLOAT,
		FORMAT_RGB_BP_SFLOAT,
		FORMAT_RGBA_BP_UNORM,
		FORMAT_RGBA_BP_SRGB,

		FORMAT_RGB_ETC2_UNORM,
		FORMAT_RGB_ETC2_SRGB,
		FORMAT_RGBA_ETC2_A1_UNORM,
		FORMAT_RGBA_ETC2_A1_SRGB,
		FORMAT_RGBA_ETC2_UNORM,
		FORMAT_RGBA_ETC2_SRGB,
		FORMAT_R_EAC_UNORM,
		FORMAT_R_EAC_SNORM,
		FORMAT_RG_EAC_UNORM,
		FORMAT_RG_EAC_SNORM,

		FORMAT_RGBA_ASTC_4X4_UNORM,
		FORMAT_RGBA_ASTC_4X4_SRGB,
		FORMAT_RGBA_ASTC_5X4_UNORM,
		FORMAT_RGBA_ASTC_5X4_SRGB,
		FORMAT_RGBA_ASTC_5X5_UNORM,
		FORMAT_RGBA_ASTC_5X5_SRGB,
		FORMAT_RGBA_ASTC_6X5_UNORM,
		FORMAT_RGBA_ASTC_6X5_SRGB,
		FORMAT_RGBA_ASTC_6X6_UNORM,
		FORMAT_RGBA_ASTC_6X6_SRGB,
		FORMAT_RGBA_ASTC_8X5_UNORM,
		FORMAT_RGBA_ASTC_8X5_SRGB,
		FORMAT_RGBA_ASTC_8X6_UNORM,
		FORMAT_RGBA_ASTC_8X6_SRGB,
		FORMAT_RGBA_ASTC_8X8_UNORM,
		FORMAT_RGBA_ASTC_8X8_SRGB,
		FORMAT_RGBA_ASTC_10X5_UNORM,
		FORMAT_RGBA_ASTC_10X5_SRGB,
		FORMAT_RGBA_ASTC_10X6_UNORM,
		FORMAT_RGBA_ASTC_10X6_SRGB,
		FORMAT_RGBA_ASTC_10X8_UNORM,
		FORMAT_RGBA_ASTC_10X8_SRGB,
		FORMAT_RGBA_ASTC_10X10_UNORM,
		FORMAT_RGBA_ASTC_10X10_SRGB,
		FORMAT_RGBA_ASTC_12X10_UNORM,
		FORMAT_RGBA_ASTC_12X10_SRGB,
		FORMAT_RGBA_ASTC_12X12_UNORM,
		FORMAT_RGBA_ASTC_12X12_SRGB,

		FORMAT_RGB_PVRTC1_8X8_UNORM,
		FORMAT_RGB_PVRTC1_8X8_SRGB,
		FORMAT_RGB_PVRTC1_16X8_UNORM,
		FORMAT_RGB_PVRTC1_16X8_SRGB,
		FORMAT_RGBA_PVRTC1_8X8_UNORM,
		FORMAT_RGBA_PVRTC1_8X8_SRGB,
		FORMAT_RGBA_PVRTC1_16X8_UNORM,
		FORMAT_RGBA_PVRTC1_16X8_SRGB,
		FORMAT_RGBA_PVRTC2_4X4_UNORM,
		FORMAT_RGBA_PVRTC2_4X4_SRGB,
		FORMAT_RGBA_PVRTC2_8X4_UNORM,
		FORMAT_RGBA_PVRTC2_8X4_SRGB,

		FORMAT_RGB_ETC_UNORM,
		FORMAT_RGB_ATC_UNORM,
		FORMAT_RGBA_ATC_EXPLICIT_UNORM,
		FORMAT_RGBA_ATC_INTERPOLATED_UNORM,

		FORMAT_L8_UNORM,
		FORMAT_A8_UNORM,
		FORMAT_LA8_UNORM,
		FORMAT_L16_UNORM,
		FORMAT_A16_UNORM,
		FORMAT_LA16_UNORM,

		FORMAT_BGR8_UNORM_PACK32,
		FORMAT_BGR8_SRGB_PACK32,

		FORMAT_RG3B2_UNORM_PACK8, FORMAT_LAST = FORMAT_RG3B2_UNORM_PACK8
	};

	enum swizzle
	{
		SWIZZLE_RED, SWIZZLE_FIRST = SWIZZLE_RED, SWIZZLE_CHANNEL_FIRST = SWIZZLE_RED,
		SWIZZLE_GREEN,
		SWIZZLE_BLUE,
		SWIZZLE_ALPHA, SWIZZLE_CHANNEL_LAST = SWIZZLE_ALPHA,
		SWIZZLE_ZERO,
		SWIZZLE_ONE, SWIZZLE_LAST = SWIZZLE_ONE
	};

	inline bool is_channel(swizzle Swizzle)
	{
		return Swizzle >= SWIZZLE_CHANNEL_FIRST && Swizzle <= SWIZZLE_CHANNEL_LAST;
	}

	enum
	{
		FORMAT_INVALID = -1,
		FORMAT_COUNT = FORMAT_LAST - FORMAT_FIRST + 1,
		SWIZZLE_COUNT = SWIZZLE_LAST - SWIZZLE_FIRST + 1
	};

	inline bool is_valid(format Format)
	{
		return Format >= FORMAT_FIRST && Format <= FORMAT_LAST;
	}

	typedef glm::tvec4<swizzle> swizzles;

	bool is_compressed(format Format);
	bool is_srgb(format Format);
	size_t block_size(format Format);
	ivec3 block_dimensions(format Format);
	size_t component_count(format Format);
}//namespace gli

#include "./core/format.inl"
