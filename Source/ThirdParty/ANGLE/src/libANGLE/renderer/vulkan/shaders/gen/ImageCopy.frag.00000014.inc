// GENERATED FILE - DO NOT EDIT.
// Generated by gen_vk_internal_shaders.py.
//
// Copyright 2018 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// shaders/gen/ImageCopy.frag.00000014.inc:
//   Pre-generated shader for the ANGLE Vulkan back-end.

#pragma once
constexpr uint8_t kImageCopy_frag_00000014[] = {
    0x1f,0x8b,0x08,0x00,0x00,0x00,0x00,0x00,0x02,0xff,0x85,0x98,0xf7,0x73,0x55,0x55,
    0x10,0xc7,0x6f,0xde,0x7b,0x79,0x0f,0x42,0x0b,0x12,0x43,0x11,0x9c,0x24,0x14,0xd1,
    0x60,0x40,0x0d,0x84,0xf6,0xa8,0x4a,0x51,0x6a,0x02,0x0a,0x62,0x84,0x20,0x2a,0x20,
    0x04,0x25,0x51,0x04,0x69,0x41,0x94,0xa0,0x08,0x22,0x16,0x40,0x05,0x54,0x50,0x09,
    0x52,0x54,0x9a,0x80,0x82,0xd2,0x2c,0x44,0x54,0x40,0x05,0x01,0xfd,0xc9,0xff,0xc0,
    0xb1,0xcc,0x58,0xce,0x9e,0x7c,0x36,0xb3,0x73,0x27,0x6a,0x66,0xce,0xdc,0xb7,0xdf,
    0xdd,0xb3,0xfb,0xdd,0x72,0xce,0x7d,0x2f,0xd1,0x48,0xdb,0x44,0x10,0xa4,0x04,0x69,
    0x41,0xbd,0xe0,0xa7,0xa0,0xe6,0xaf,0x69,0x10,0x71,0x48,0x10,0x34,0x08,0xe2,0xfe,
    0x39,0x78,0x58,0xd1,0xb0,0xbc,0xb2,0xf2,0x29,0x79,0xf9,0x5d,0xbb,0x88,0xbe,0x71,
    0x10,0xf5,0x76,0xa2,0x6b,0x12,0x24,0x82,0x98,0x7b,0xca,0x9a,0x59,0x32,0xad,0x54,
    0xf0,0x0e,0x6e,0x5d,0x76,0x2b,0xdd,0xd9,0x09,0x9e,0x10,0x1f,0xee,0x53,0x07,0xef,
    0x53,0xf6,0x04,0xc1,0x90,0x20,0x35,0xe8,0x44,0xbc,0xb6,0x3c,0x15,0x4b,0x01,0xab,
    0x67,0xb0,0x08,0x58,0xba,0xc1,0xa2,0x60,0x19,0x06,0x8b,0x81,0xb5,0x30,0x58,0x2a,
    0x58,0x6b,0x83,0xc5,0xc1,0xb2,0x0c,0x96,0x00,0x6b,0x67,0xb0,0x7a,0x60,0x1d,0x0d,
    0x56,0x1f,0xac,0x93,0xc1,0xd2,0xc0,0xba,0x18,0xac,0x01,0x58,0xbe,0xc1,0x1a,0x82,
    0x75,0x37,0x58,0x23,0xb0,0xde,0xbe,0x4e,0xd1,0xda,0x7c,0xa5,0x66,0x13,0xdc,0x33,
    0x87,0xfa,0xa8,0x9c,0x6d,0x64,0xa9,0xf3,0xd5,0xc8,0xcd,0xdc,0xae,0x88,0xd7,0x47,
    0x7d,0x6d,0xe4,0x73,0xa6,0xfb,0x14,0x27,0xcf,0x2c,0x67,0x9f,0x20,0xcf,0xb8,0xb7,
    0x8b,0xf9,0xfc,0xe2,0x60,0xb9,0x4e,0x8e,0xc3,0xe7,0xe7,0x1d,0xed,0x93,0x19,0xce,
    0x43,0x63,0x83,0x37,0x73,0xab,0x70,0xff,0x88,0xfe,0x2a,0x4b,0x8d,0x77,0x0c,0x2e,
    0x49,0xaa,0xdc,0xca,0xad,0x64,0xda,0xb2,0xbe,0x2a,0x4b,0xbd,0xd7,0xaf,0x6b,0xd9,
    0xef,0x4a,0x27,0x67,0xc1,0x41,0x7a,0xdb,0xdc,0xc9,0xd9,0xc8,0x11,0x78,0xe5,0xc0,
    0x21,0x1b,0x7d,0x3b,0x78,0xc5,0xd0,0xb7,0x67,0xaf,0xe0,0xbd,0x90,0x3b,0x18,0x7f,
    0xd7,0x60,0x2f,0xfe,0x24,0x5e,0x2e,0xfe,0x03,0x5f,0x9f,0x74,0x5f,0xd3,0x6c,0x96,
    0x72,0xc9,0xfd,0x9f,0x95,0x55,0xfb,0x8c,0x05,0xd7,0xd3,0xf7,0x4e,0xc4,0x17,0x39,
    0x0f,0x2c,0x97,0xfc,0x3a,0xc3,0x47,0xec,0xbb,0xa0,0xcb,0x36,0xfa,0x6e,0x26,0x9f,
    0x82,0xda,0xbd,0x35,0x7a,0x79,0xf6,0x84,0xaf,0xe8,0xfb,0x50,0x8f,0x2c,0xb3,0x7f,
    0x20,0xb3,0xac,0xf6,0x43,0x89,0xa7,0xfa,0x11,0xf4,0x4e,0xea,0x71,0x3b,0x7b,0x35,
    0xde,0x1d,0xf8,0x13,0xbc,0xa5,0x8b,0x3c,0xde,0xf4,0x23,0xa8,0xe3,0x29,0x7b,0xee,
    0xe4,0xf3,0x78,0x72,0x16,0x79,0x02,0x98,0xc6,0x2c,0x0e,0xc9,0x93,0x39,0x97,0xb2,
    0xff,0x1e,0x72,0xcc,0x82,0xd3,0x7d,0x7c,0x8e,0x1a,0xfb,0xe9,0xf4,0x4c,0xe5,0x52,
    0xfa,0xa8,0x39,0x96,0x87,0xec,0x17,0xd6,0xd6,0x25,0x16,0x3c,0xc7,0xe7,0x76,0x66,
    0x46,0x5f,0xf4,0x6c,0x16,0x0d,0x54,0xfb,0xf5,0x9c,0x43,0xf5,0xb7,0x2d,0x14,0x6f,
    0x17,0x67,0x5c,0xe5,0x83,0xa1,0x9e,0x9e,0xe0,0xcc,0xaa,0xff,0x2f,0x4d,0xbe,0x22,
    0xff,0xe0,0xa5,0xc5,0x7d,0x85,0xcf,0x25,0xb8,0xea,0x8c,0x5e,0xe2,0x1e,0x8c,0xfa,
    0xde,0xa7,0xfa,0xb8,0x31,0xf6,0x0b,0xf6,0x9b,0x43,0x52,0xb1,0xcd,0xe1,0x0e,0x48,
    0x18,0x39,0xdf,0xc8,0xd2,0xbf,0x71,0x46,0x96,0xdc,0xd7,0x18,0x59,0x9e,0x9b,0x42,
    0xf2,0x96,0x90,0x5c,0x65,0x64,0x99,0xaf,0xe3,0xc8,0x49,0xce,0x5b,0x47,0xce,0xd4,
    0x48,0x87,0xca,0x79,0xba,0x16,0xac,0xa3,0x99,0x8d,0x52,0xce,0xee,0x75,0xe8,0xfb,
    0xbb,0x0c,0x64,0xd6,0x6f,0xe0,0x3c,0x74,0xc6,0x9f,0xd8,0xdc,0x08,0xbe,0xc4,0xd9,
    0x88,0x7c,0x13,0xfb,0x04,0xef,0xe3,0x2a,0xd0,0x16,0x4c,0xed,0xbb,0x52,0x03,0xd1,
    0xe5,0x23,0x8b,0xff,0x02,0xee,0xcb,0x3c,0xce,0x50,0x92,0x5e,0xf6,0x00,0xdf,0xe6,
    0x6c,0x1a,0xfb,0xbc,0x6a,0x30,0x39,0x47,0xbf,0x3a,0x1f,0x49,0x78,0xff,0xe1,0xec,
    0x7b,0x71,0xbf,0x26,0xa9,0x7b,0x6f,0x7c,0x4b,0x1d,0xfa,0x52,0xeb,0x9e,0xf8,0x96,
    0xbe,0xf7,0x03,0x5f,0x88,0xdc,0x1f,0x4c,0xf7,0x0c,0x30,0x7b,0x84,0xef,0x00,0x6c,
    0x7e,0x77,0xbe,0x35,0x46,0xd2,0xf0,0xbf,0x19,0xfe,0x03,0x0d,0xff,0x5b,0xc0,0x95,
    0xff,0x20,0x30,0xe5,0x3f,0xc4,0xf0,0x1f,0xe4,0xef,0xfb,0xc0,0x63,0xe2,0x7b,0xb0,
    0xe1,0x72,0x2b,0x5c,0x86,0x1a,0xfe,0xb7,0x81,0x2b,0xff,0x61,0x60,0xba,0x67,0xb8,
    0xd9,0x23,0xfc,0x87,0x63,0x23,0xfc,0x35,0xc6,0x10,0xc3,0x7f,0x24,0xfc,0x47,0x18,
    0xfe,0xa3,0xc0,0x95,0xff,0x68,0x30,0xe5,0x5f,0x64,0xf8,0x8b,0xae,0xd0,0xad,0x22,
    0x7c,0x17,0x9a,0xbe,0x8f,0x81,0x8b,0xcc,0x9d,0xc8,0x63,0xc1,0xc6,0x98,0xfb,0x48,
    0x67,0x62,0x2c,0x1c,0xd5,0x4f,0x11,0x7e,0xe4,0x8e,0xba,0x8b,0xfb,0x49,0x67,0xf2,
    0x6e,0x38,0x17,0x9b,0x58,0x13,0xc1,0x55,0x9e,0x44,0xec,0xc5,0xcc,0x68,0x09,0x36,
    0x93,0xf0,0x23,0x77,0xd8,0x14,0xfc,0x4c,0x36,0xf5,0xbd,0x17,0x7c,0xb4,0xb3,0x11,
    0xf9,0x7e,0xf6,0x06,0x06,0x9b,0x0a,0x96,0xe2,0xeb,0x12,0xf7,0xf7,0xdf,0x34,0x6c,
    0xa7,0xe2,0x43,0x63,0x3c,0x40,0x8c,0xe9,0x26,0xc6,0x0c,0xf0,0x89,0xae,0x2e,0x72,
    0x6f,0xcf,0x24,0xc7,0x69,0xdc,0x61,0x33,0xa8,0xcb,0x38,0x74,0xda,0xab,0x59,0xf8,
    0x2a,0x35,0xbd,0x7a,0x10,0x5c,0x7b,0xf5,0x10,0x98,0xf6,0xaa,0xcc,0xf4,0x4a,0x74,
    0xb3,0xdd,0x5a,0x40,0x8d,0x67,0x9b,0xb9,0x79,0x98,0x7b,0xa8,0xdc,0xf0,0x7c,0x04,
    0x3c,0xc9,0x7b,0x67,0x0e,0x36,0x23,0xdd,0xcd,0x2a,0x39,0x3f,0x0a,0x36,0xc7,0xdc,
    0x23,0x11,0x53,0x93,0xb9,0xf8,0xd0,0xb5,0xd4,0xc5,0x12,0x7c,0x1e,0x7b,0xe7,0x1a,
    0xdf,0x8f,0xd5,0xfa,0xae,0xef,0xe5,0xf9,0x60,0xf3,0xb8,0x5b,0x53,0x79,0x7f,0x44,
    0x4d,0x6d,0xe6,0x33,0x33,0x65,0xe4,0xb3,0xc0,0xd4,0x6a,0x11,0xb5,0x5a,0x68,0x6a,
    0xb5,0x18,0x5c,0x6b,0x55,0x01,0xa6,0xb5,0x7a,0xdc,0xd4,0xaa,0xc2,0xdf,0x6f,0x81,
    0xc7,0xc4,0xf7,0x12,0x53,0xab,0xa5,0x75,0xd4,0xea,0x09,0xf0,0xed,0xf8,0x7e,0x12,
    0xac,0x18,0x8e,0xea,0x47,0x9e,0xbf,0xb8,0xbe,0x8b,0xcd,0x32,0x38,0x2c,0xc0,0x7e,
    0x09,0x3c,0x96,0x1b,0x1e,0x62,0x53,0xe9,0xd6,0x72,0xf6,0x57,0x1a,0x1e,0x4f,0xd5,
    0xc1,0xe3,0x69,0x70,0xad,0xeb,0x8a,0x50,0xcf,0x9e,0x01,0x5b,0xf1,0x2f,0x3d,0x5b,
    0x89,0x0f,0x5d,0xcb,0xe8,0xd9,0x2a,0xf6,0xae,0x34,0xbe,0x9f,0x0d,0xf5,0x6c,0x35,
    0xd8,0xaa,0xff,0xe8,0xd9,0x6a,0xea,0xa1,0xf9,0x2c,0x0f,0xf5,0xb0,0xcc,0xf8,0x7f,
    0x1e,0xff,0xb3,0x78,0x8f,0xbd,0x00,0x26,0xbe,0xd6,0x20,0xeb,0x3b,0xee,0x25,0xde,
    0x9b,0xa3,0x5c,0x6d,0x45,0x5e,0xcb,0x77,0x06,0xbb,0x2a,0x1d,0x23,0xd1,0xad,0xc3,
    0x7e,0xad,0xf1,0xb5,0xce,0xcc,0xce,0xcb,0xcc,0xce,0x7a,0x33,0x3b,0xaf,0x80,0xeb,
    0xec,0xbc,0x0a,0xa6,0xb3,0xb3,0xd1,0xf4,0x4c,0x74,0x1b,0xdc,0xda,0x48,0x4e,0x1b,
    0xf0,0x2d,0xef,0xe4,0xd7,0xe0,0xa9,0xef,0x24,0xa9,0xcf,0xeb,0xe0,0xc2,0x65,0x13,
    0x72,0x0f,0x67,0x2f,0xba,0x37,0xf8,0x0d,0xb2,0xc9,0xf8,0xd8,0x6c,0x7c,0xc8,0x9e,
    0xcd,0xd8,0xa9,0xfe,0x4d,0xf4,0x43,0x4d,0x8c,0xb7,0xc0,0xc5,0x7e,0x0b,0xb2,0xc6,
    0x78,0x9b,0x18,0x5b,0x8c,0x8f,0xad,0xc6,0x87,0xec,0xd9,0x8a,0x9d,0xea,0xdf,0x41,
    0xbf,0xcd,0xc4,0xd8,0x0e,0x2e,0xf6,0x55,0xc8,0x1a,0x63,0x07,0x31,0xaa,0x8c,0x8f,
    0x9d,0xc6,0x87,0xec,0xd9,0x89,0x9d,0xcc,0x83,0xd6,0x6e,0xa3,0xe9,0xcb,0xbb,0xf4,
    0x65,0x97,0xe9,0xcb,0x7b,0xe0,0xda,0x97,0xf7,0xc1,0xb4,0x2f,0x7b,0x4c,0x5f,0x44,
    0xb7,0xdb,0xad,0x03,0xf8,0xde,0x6d,0xe6,0x67,0x2f,0x5c,0xf4,0x3b,0xd2,0x3e,0xb0,
    0xbd,0xe6,0x7b,0x9d,0xda,0xee,0xaf,0xb5,0xad,0xef,0xe5,0x0f,0xc0,0xf6,0x99,0xb9,
    0x8f,0x98,0xb9,0x5f,0x83,0x8d,0xe4,0xb5,0x87,0xd8,0x07,0x4c,0x5e,0x87,0xc8,0xeb,
    0xa0,0xc9,0xeb,0x43,0x70,0xcd,0xeb,0x23,0x30,0xcd,0xeb,0x88,0xc9,0x4b,0x74,0x87,
    0xdd,0x3a,0x86,0xef,0xc3,0xa6,0xc6,0x1f,0xc3,0xb5,0xdc,0xf4,0xe9,0x13,0x70,0xb5,
    0x39,0x1a,0x9a,0xa7,0xa3,0xd8,0x08,0xdf,0x23,0xf8,0x3c,0x66,0xde,0x69,0x27,0xe1,
    0x7b,0xc2,0xdc,0x3b,0x9f,0x82,0xcb,0xfe,0xe3,0xc8,0xaa,0xfb,0x8c,0xef,0xa4,0x27,
    0x79,0x7f,0x7e,0x0e,0x36,0xdd,0xe4,0xf7,0x05,0x78,0x31,0xf9,0x55,0x9b,0xfc,0x44,
    0x77,0xca,0xad,0x6a,0xb8,0x9c,0x32,0xdc,0x4f,0x87,0xe6,0xf4,0x34,0xdf,0xe5,0x85,
    0xbb,0xda,0x57,0x1b,0x2e,0x5f,0x85,0xb8,0x7c,0x0d,0xd6,0xcd,0x70,0xf9,0x06,0x5c,
    0xb9,0x9c,0x35,0x5c,0x44,0x77,0xc6,0xad,0xb3,0xf8,0x3e,0x63,0xb8,0x9c,0x0b,0xcd,
    0xf3,0x39,0xc3,0x45,0xed,0xcf,0x1a,0x2e,0xdf,0x86,0xb8,0x7c,0x07,0xb6,0xcb,0x70,
    0xf9,0x1e,0x5c,0xb9,0x5c,0x30,0x5c,0x44,0x77,0xde,0xad,0x0b,0xf8,0x3e,0x6f,0xb8,
    0x5c,0x34,0x7d,0x17,0x2e,0x17,0xf9,0x4d,0x23,0x5c,0xd4,0xfe,0x42,0xa8,0xc7,0x47,
    0x42,0x33,0xba,0xc7,0xcc,0xfc,0x8f,0xf8,0x13,0x5f,0x97,0x91,0xff,0x74,0x6f,0x8f,
    0xee,0x6e,0x75,0xe3,0x8c,0xa7,0xc1,0x4d,0x7e,0x77,0x15,0x38,0xbb,0x04,0xbf,0xb9,
    0xc4,0x57,0x03,0x33,0x7f,0x0d,0xc1,0x0f,0x91,0x63,0x13,0xb0,0x46,0xe4,0xd8,0xd4,
    0xe4,0xd8,0x84,0xff,0x0d,0x65,0xe2,0x27,0xdd,0xf8,0xb9,0x02,0x3f,0x95,0xc4,0xcf,
    0x00,0x93,0xff,0x67,0xfc,0xe5,0x6c,0x33,0xd8,0x93,0x69,0xf6,0x34,0x67,0x4f,0x05,
    0x7b,0x5a,0x82,0xb5,0x30,0x7e,0xae,0x02,0x6f,0xe5,0x79,0x25,0x3c,0xd6,0x86,0x77,
    0x65,0x2b,0xf4,0xad,0x89,0xd1,0x86,0x18,0xc2,0xf9,0x6f,0xea,0xf1,0x0f,0x7b,0xec,
    0xb6,0x89,0x7c,0x13,0x00,0x00
};

// Generated from:
//
// #version 450 core
//
// #extension GL_EXT_samplerless_texture_functions : require
//
// layout(set = 0, binding = 0)uniform itexture2DArray src;
// layout(location = 0)out vec4 dst;
//
// layout(push_constant)uniform PushConstants {
//
//     ivec2 srcOffset;
//     ivec2 dstOffset;
//     int srcMip;
//     int srcLayer;
//
//     bool flipX;
//     bool flipY;
//
//     bool premultiplyAlpha;
//     bool unmultiplyAlpha;
//
//     bool dstHasLuminance;
//     bool dstIsAlpha;
//
//     bool srcIsSRGB;
//     bool dstIsSRGB;
//
//     int dstDefaultChannelsMask;
//     bool rotateXY;
// } params;
//
// float sRGBToLinear(float sRGB)
// {
//
//     if(sRGB <= 0.04045)
//     {
//         return sRGB / 12.92;
//     }
//     else
//     {
//         return pow((sRGB + 0.055f)/ 1.055f, 2.4f);
//     }
// }
//
// void main()
// {
//     ivec2 dstSubImageCoords = ivec2(gl_FragCoord . xy)- params . dstOffset;
//
//     ivec2 srcSubImageCoords = dstSubImageCoords;
//
//     if(params . flipX)
//     {
//         srcSubImageCoords . x = - srcSubImageCoords . x;
//     }
//     if(params . flipY)
//     {
//         srcSubImageCoords . y = - srcSubImageCoords . y;
//     }
//     if(params . rotateXY)
//     {
//         srcSubImageCoords . xy = srcSubImageCoords . yx;
//     }
//
//           ivec4 srcValue = texelFetch(src, ivec3(params . srcOffset + srcSubImageCoords, params . srcLayer), params . srcMip);
//
//     if(params . premultiplyAlpha)
//     {
//         srcValue . rgb *= srcValue . a;
//     }
//     else if(params . unmultiplyAlpha && srcValue . a > 0)
//     {
//         srcValue . rgb /= srcValue . a;
//     }
//
//            vec4 dstValue = vec4(srcValue);
//
//     dstValue /= 255.0;
//
//     if(params . dstIsSRGB)
//     {
//
//         dstValue . r = sRGBToLinear(dstValue . r);
//         dstValue . g = sRGBToLinear(dstValue . g);
//         dstValue . b = sRGBToLinear(dstValue . b);
//     }
//
//     if(params . dstHasLuminance)
//     {
//         dstValue . rg = dstValue . ra;
//     }
//     else if(params . dstIsAlpha)
//     {
//         dstValue . r = dstValue . a;
//     }
//     else
//     {
//         int defaultChannelsMask = params . dstDefaultChannelsMask;
//         if((defaultChannelsMask & 2)!= 0)
//         {
//             dstValue . g = 0;
//         }
//         if((defaultChannelsMask & 4)!= 0)
//         {
//             dstValue . b = 0;
//         }
//         if((defaultChannelsMask & 8)!= 0)
//         {
//             dstValue . a = 1;
//         }
//     }
//
//     dst = dstValue;
// }