#include "../../inc/cub3d.h"

double	deg_to_rad(double value)
{
	return (value * M_PI / 180);
}

double	square(double value)
{
	return (value * value);
}

void	define_color(t_texture *color, t_texture *zone)
{
	color->r = zone->r;
	color->g = zone->g;
	color->b = zone->b;
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * img->linelen + x * (img->bpp / 8));
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

int	color_picker(unsigned char red, unsigned char green,
		unsigned char blue)
{
	return (red << 16 | green << 8 | blue);
}
