#include "../../include/cub3d.h"

//crea a partir del archivo la bidimensional con el mapa
int	ft_create_bid(t_in *dt)
{
	int	i;
	int	j;

	if (ft_ch_line_first(dt->info) == -1)
		return (-1);
	dt->map = (char **) malloc (sizeof(char *) * (ft_count_fd (dt->info, 2) + 1));
	if (!dt->map)
		return (-1);
	i = -1;
	j = -1;
	while (dt->info[++i])
	{
		if (ft_check_line (dt->info[i], 2) == 0)
		{
			dt->map[++j] = ft_dup(dt->info[i]);
		}
	}
	dt->map[++j] = NULL;
	if (ft_data_map(dt) == -1)
		return (-1);
	return (0);
}

//evaluo todas las lineas del archivo mapa para que no haya ninguna que empieza por algo indevido
int	ft_ch_line_first(char **info)
{
	int	i;
	int	j;

	i = -1;
	while (info[++i])
	{
		j = 0;
		while (info[i][j] == ' ')
			j++;
		if (info[i][j] != 'N' && info[i][j] != 'S' && info[i][j] != 'E' && info[i][j] != 'W' && info[i][j] != 'C' && info[i][j] != 'F' && info[i][j] != '1' && info[i][j] != '0')
		{
			printf ("Error\nForbiden line text\n");
			return (-1);
		}
	}
	return (0);
}

//cuenta la cantidad de lineas, o de datos (1) o de mapa (2)
int	ft_count_fd(char **info, int n)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (info[i])
	{
		if (ft_check_line (info[i], n) == 0)
			r++;
		i++;
	}
	return (r);
}

//chequeo si la linea vale para datos (n = 1) o para mapa (n = 2)
int	ft_check_line(char *line, int n)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] && line[i] == ' ') //avanzo los espacios en blanco
		i++;
	if (n == 1 && line[i] && line[i + 1]) //control de datos de texturas
	{
		if ((((line[i] == 'N' || line[i] == 'S') && line[i + 1] == 'O') || (line[i] == 'E' && line[i + 1] == 'A') || (line[i] == 'W' && line [i + 1] == 'E')) && line[i + 2] == ' ')
			return (0);
	}
	else if (n == 2 && line[i]) //control de mapas
	{
		if (((line[i] == 'N' || line[i] == 'S') && line[i + 1] == 'O') || (line[i] == 'E' && line[i + 1] == 'A') || (line[i] == 'W' && line [i + 1] == 'E'))
			return (1);
		if ((line[i] == 'F' || line[i] == 'C') && (line[i + 1] == ' '))
			return (1);
		else
			return (0);
	}
	return (1);
}

//funcion que guarda el numero de filas y columnas del mapa.
//Si no son > 4 da error de dimension
int	ft_data_map(t_in *dt)
{
	int	j;

	dt->maxy = 0;
	dt->maxx = 0;
	while (dt->map[dt->maxy])
	{
		j = ft_strlen(dt->map[dt->maxy]);
		if (j > dt->maxx)
			dt->maxx = j;
		dt->maxy++;
	}
	if (dt->maxy < 4 || dt->maxx < 4)
	{
		printf ("Error\nBad map dimension - Error map\n");
		return (-1);
	}
	return (0);
}

//cambia el map añadiendo espacios en los huecos vacios a la derecha y asi regularizar el map
char	**ft_add_columns(t_in *dt)
{
	char	**aux;
	int		i;
	int		j;

	aux = (char **) malloc (sizeof(char *) * (dt->maxy + 1));
	if (!aux)
		return (NULL);
	i = 0;
	while (dt->map[i])
	{
		aux[i] = (char *) malloc (sizeof(char) * (dt->maxx + 1));
		j = -1;
		while (dt->map[i][++j])
			aux[i][j] = dt->map[i][j];
		while (j < dt->maxx)
			aux[i][j++] = ' ';
		aux[i][j] = 00;
		free (dt->map[i++]);
	}
	aux[i] = NULL;
	free (dt->map);
	return (aux);
}
