#include "bmp.h"

typedef struct __attritube__((packed)) BITMAPFILEHEADER
{
	uint16_t bf_type;
	uint32_t bf_size;
	uint16_t bf_reserved1;
	uint16_t bf_reserved2;
	uint32_t bf_offbits;
} BITMAPFILEHEADER;

typedef struct __attritube__((packed)) BITMAPINFOHEADER
{
	uint32_t bi_size;
	uint32_t bi_width;
	uint32_t bi_height;
	uint16_t bi_planes;
	uint16_t bi_bitcount;
	uint32_t bi_compression;
	uint32_t bi_size_image;
	uint32_t bi_x_pels_per_meter;
	uint32_t bi_y_pels_per_meter;
	uint32_t bi_clr_used;
	uint32_t bi_clr_important;
} BITMAPINFOHEADER;

const BITMAPFILEHEADER dst_head = {
	.bf_type = 19778,
	.bf_size = 766136,
	.bf_reserved1 = 0;
}
