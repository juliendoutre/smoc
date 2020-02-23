/*
 * engine.h
 *
 *  Created on: 17 déc. 2019
 *      Author: Julien
 */

unsigned char img_favicon[] = {
    0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x10, 0x10, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x68, 0x05, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0x00, 0x01, 0x01, 0xff, 0x00, 0x02, 0x02, 0xff, 0x00, 0x03, 0x03, 0xff, 0x00, 0x04, 0x04, 0xff, 0x00, 0x05, 0x05, 0xff, 0x00, 0x06, 0x06, 0xff, 0x00, 0x08, 0x08, 0xff, 0x00, 0x09, 0x09,
    0xff, 0x00, 0x0d, 0x0d, 0xff, 0x00, 0x10, 0x10, 0xff, 0x00, 0x13, 0x13, 0xff, 0x00, 0x14, 0x14, 0xff, 0x00, 0x17, 0x17, 0xff, 0x00, 0x19, 0x19, 0xff, 0x00, 0x1f, 0x1f, 0xff, 0x00, 0x21, 0x21,
    0xff, 0x00, 0x24, 0x24, 0xff, 0x00, 0x28, 0x28, 0xff, 0x00, 0x2a, 0x2a, 0xff, 0x00, 0x2b, 0x2b, 0xff, 0x00, 0x2c, 0x2c, 0xff, 0x00, 0x2e, 0x2e, 0xff, 0x00, 0x2f, 0x2f, 0xff, 0x00, 0x31, 0x31,
    0xff, 0x00, 0x34, 0x34, 0xff, 0x00, 0x35, 0x35, 0xff, 0x00, 0x37, 0x37, 0xff, 0x00, 0x39, 0x39, 0xff, 0x00, 0x3d, 0x3d, 0xff, 0x00, 0x40, 0x40, 0xff, 0x00, 0x41, 0x41, 0xff, 0x00, 0x43, 0x43,
    0xff, 0x00, 0x44, 0x44, 0xff, 0x00, 0x48, 0x48, 0xff, 0x00, 0x49, 0x49, 0xff, 0x00, 0x4a, 0x4a, 0xff, 0x00, 0x4d, 0x4d, 0xff, 0x00, 0x4e, 0x4e, 0xff, 0x00, 0x4f, 0x4f, 0xff, 0x00, 0x50, 0x50,
    0xff, 0x00, 0x54, 0x54, 0xff, 0x00, 0x59, 0x59, 0xff, 0x00, 0x5b, 0x5b, 0xff, 0x00, 0x5e, 0x5e, 0xff, 0x00, 0x61, 0x61, 0xff, 0x00, 0x62, 0x62, 0xff, 0x00, 0x65, 0x65, 0xff, 0x00, 0x66, 0x66,
    0xff, 0x00, 0x6a, 0x6a, 0xff, 0x00, 0x6d, 0x6d, 0xff, 0x00, 0x71, 0x71, 0xff, 0x00, 0x72, 0x72, 0xff, 0x00, 0x73, 0x73, 0xff, 0x00, 0x78, 0x78, 0xff, 0x00, 0x7e, 0x7e, 0xff, 0x00, 0x80, 0x80,
    0xff, 0x00, 0x81, 0x81, 0xff, 0x00, 0x84, 0x84, 0xff, 0x00, 0x89, 0x89, 0xff, 0x00, 0x8a, 0x8a, 0xff, 0x00, 0x8b, 0x8b, 0xff, 0x00, 0x8d, 0x8d, 0xff, 0x00, 0x8f, 0x8f, 0xff, 0x00, 0x91, 0x91,
    0xff, 0x00, 0x93, 0x93, 0xff, 0x00, 0x97, 0x97, 0xff, 0x00, 0x99, 0x99, 0xff, 0x00, 0x9a, 0x9a, 0xff, 0x00, 0x9b, 0x9b, 0xff, 0x00, 0x9c, 0x9c, 0xff, 0x00, 0x9d, 0x9d, 0xff, 0x00, 0x9f, 0x9f,
    0xff, 0x00, 0xa0, 0xa0, 0xff, 0x00, 0xa5, 0xa5, 0xff, 0x00, 0xa6, 0xa6, 0xff, 0x00, 0xa7, 0xa7, 0xff, 0x00, 0xa8, 0xa8, 0xff, 0x00, 0xac, 0xac, 0xff, 0x00, 0xae, 0xae, 0xff, 0x00, 0xaf, 0xaf,
    0xff, 0x00, 0xb9, 0xb9, 0xff, 0x00, 0xba, 0xba, 0xff, 0x00, 0xbf, 0xbf, 0xff, 0x00, 0xc2, 0xc2, 0xff, 0x00, 0xc5, 0xc5, 0xff, 0x00, 0xc9, 0xc9, 0xff, 0x00, 0xcc, 0xcc, 0xff, 0x00, 0xce, 0xce,
    0xff, 0x00, 0xd1, 0xd1, 0xff, 0x00, 0xd5, 0xd5, 0xff, 0x00, 0xd8, 0xd8, 0xff, 0x00, 0xda, 0xda, 0xff, 0x00, 0xdc, 0xdc, 0xff, 0x00, 0xdd, 0xdd, 0xff, 0x00, 0xde, 0xde, 0xff, 0x00, 0xdf, 0xdf,
    0xff, 0x00, 0xe1, 0xe1, 0xff, 0x00, 0xe2, 0xe2, 0xff, 0x00, 0xe3, 0xe3, 0xff, 0x00, 0xe4, 0xe4, 0xff, 0x00, 0xe6, 0xe6, 0xff, 0x00, 0xe8, 0xe8, 0xff, 0x00, 0xea, 0xea, 0xff, 0x00, 0xec, 0xec,
    0xff, 0x00, 0xee, 0xee, 0xff, 0x00, 0xef, 0xef, 0xff, 0x00, 0xf5, 0xf5, 0xff, 0x00, 0xfb, 0xfb, 0xff, 0x00, 0xfc, 0xfc, 0xff, 0x00, 0xfe, 0xfe, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x51, 0x61, 0x55, 0x22, 0x00, 0x00, 0x2d, 0x59, 0x5f, 0x45, 0x09, 0x00, 0x00, 0x00, 0x09,
    0x65, 0x3a, 0x0e, 0x30, 0x6b, 0x11, 0x1d, 0x6a, 0x1e, 0x0f, 0x52, 0x3f, 0x00, 0x00, 0x00, 0x25, 0x69, 0x04, 0x00, 0x00, 0x57, 0x34, 0x41, 0x4a, 0x00, 0x00, 0x12, 0x30, 0x00, 0x00, 0x00, 0x2b,
    0x60, 0x00, 0x00, 0x00, 0x52, 0x38, 0x49, 0x43, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x14, 0x6c, 0x13, 0x00, 0x0c, 0x69, 0x27, 0x32, 0x5b, 0x06, 0x00, 0x31, 0x48, 0x00, 0x00, 0x00, 0x00,
    0x3e, 0x66, 0x4b, 0x60, 0x50, 0x03, 0x08, 0x53, 0x59, 0x4e, 0x68, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x29, 0x1a, 0x01, 0x00, 0x00, 0x03, 0x1d, 0x28, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0e, 0x36, 0x3c, 0x26, 0x00, 0x10, 0x2c, 0x05, 0x37, 0x0b, 0x24, 0x19, 0x00, 0x00, 0x00, 0x07, 0x5c, 0x40, 0x2b, 0x5d, 0x2f, 0x2a, 0x56, 0x1e, 0x6e, 0x2f, 0x4a, 0x37, 0x00, 0x00, 0x00, 0x0a,
    0x47, 0x02, 0x06, 0x4f, 0x46, 0x2a, 0x56, 0x39, 0x67, 0x4b, 0x4a, 0x37, 0x00, 0x00, 0x00, 0x00, 0x18, 0x4c, 0x66, 0x61, 0x19, 0x2a, 0x56, 0x54, 0x35, 0x63, 0x4c, 0x37, 0x00, 0x00, 0x00, 0x06,
    0x64, 0x44, 0x1c, 0x1b, 0x0c, 0x2a, 0x5a, 0x6a, 0x0a, 0x5e, 0x58, 0x37, 0x00, 0x00, 0x00, 0x05, 0x61, 0x33, 0x1f, 0x62, 0x23, 0x2a, 0x6d, 0x54, 0x00, 0x46, 0x6d, 0x37, 0x00, 0x00, 0x00, 0x00,
    0x16, 0x42, 0x4d, 0x2e, 0x01, 0x0f, 0x3b, 0x21, 0x00, 0x17, 0x3d, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned long img_favicon_size = 1406;
