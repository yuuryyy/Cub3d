#include "cub3d_parse.h"

int	e_close(t_data *stuff)
{
	mlx_destroy_window(stuff->mlx, stuff->window);
	return (exit (0), 0);
}

int	x_close(t_data *stuff)
{
	mlx_destroy_window(stuff->mlx, stuff->window);
	return (exit (0), 0);
}

int	hook_press(int keycode, t_data *stuff)
{
	if (keycode == 53)
		return (e_close(stuff));
	else if (keycode == 13)
		stuff->w = 1;
	else if (keycode == 1)
		stuff->s = 1;
	else if (keycode == 124)
		stuff->rr = 1;
	else if (keycode == 123)
		stuff->rl = 1;
	else if (keycode == 0)
		stuff->a = 1;
	else if (keycode == 2)
		stuff->d = 1;
	return (0);
}

int	hook_release(int keycode, t_data *stuff)
{
	if (keycode == 13)
		stuff->w = 0;
	else if (keycode == 1)
		stuff->s = 0;
	else if (keycode == 124)
		stuff->rr = 0;
	else if (keycode == 123)
		stuff->rl = 0;
	else if (keycode == 0)
		stuff->a = 0;
	else if (keycode == 2)
		stuff->d = 0;
	return (0);
}

