/************************************************************************
** C File
** AUTHOR:   Gando
** FILE:     /Users/Gando/Desktop/Projet_P4/create_grid.c
** CREATED:  13:38:22 26/11/2020
** MODIFIED: 13:38:22 26/11/2020
************************************************************************/
 
#include "Jeu.h"

void			put_if(char	grid[][TOTAL_COL], int cond, char vrai, char faux, int x, int y)
{
	char		val_aff;
	val_aff = (cond) ? vrai : faux;
	sprintf(&grid[y][x],"%c", val_aff);
}

/*----------------------------------------------------------------------------------------*/

void			affiche_num_col()
{
	int             num_col;
	int             i;
	
	num_col = 1;
	i = 1;
	while (i < TOTAL_COL )
	{
		if ((i - 3) % 4 == 0)
		{
			printf("%d", num_col);
			num_col++;
		}
		else
			printf(" ");
		i++;
	}
	printf("\n");
}

/*----------------------------------------------------------------------------------------*/

void			affiche_grid(char grid[][TOTAL_COL])
{
	int		line;
	int		col;

	line = 0;
	while (line < TOTAL_LINE)
	{
		col = 0;
		while (col < TOTAL_COL)
		{
			printf("%c", grid[line][col]);
			col++;
		}
		printf("\n");
		line++;
	}
	affiche_num_col();
}

/*----------------------------------------------------------------------------------------*/

void			create_grid(char grid[][TOTAL_COL])
{
	int			line;
	int			col;
	int			last_col;

	line = 0;
	while (line < TOTAL_LINE)
	{
		col = 0;
		while (col < TOTAL_COL)
		{
			last_col = col % 4 == 0 ;
			if (line % 2 == 0)
				put_if(grid, last_col, 'o', '-', col, line);
			else
				put_if(grid, last_col, '|', ' ', col, line);
			col++;
		}
		line++;
	}
	return ;
}

/*----------------------------------------------------------------------------------------*/

int 			coordonne(char num_col)
{
	switch(num_col){
		case '1' : return (2);
		case '2' : return (6);
		case '3' : return (10);
		case '4' : return (14);
		case '5' : return (18);
		case '6' : return (22);
		case '7' : return (26);
		case '0' : return (0);
		case '8' : return (8);
		case '9' : return (9);
		case 'q' : return (-2);
		default : return (-1);
	}
}

/*----------------------------------------------------------------------------------------*/

void			check_joueur(ind_nb_joueur indNbrJr, char *sign)
{;
	if (indNbrJr.nbJr == '2')
	{
		if (*indNbrJr.indJr > 0)
		{
			*sign = 'O';
			printf("Joueur 1 : ");
		}
		else
		{
			*sign = 'X';
			printf("Joueur 2 : ");
		}
	}
	else if (indNbrJr.nbJr == '1')
	{
		if (*indNbrJr.indJr > 0)
		{
			*sign = 'O';
			printf("Joueur 1 : ");
		}
		else
		{
			*sign = 'X';
			printf("\nI.A :\n");
		}
	}
	else
	{
		if (*indNbrJr.indJr > 0)
		{
			*sign = 'O';
			printf("IA_1 : ");
		}
		else
		{
			*sign = 'X';
			printf("IA_2 : ");
		}
	}
	
}

/*----------------------------------------------------------------------------------------*/

coord			deplace_jeton(char grid[][TOTAL_COL], coord coordon)
{
	int		col;
	int		line;

	col = coordon.x;
	line = coordon.y;
	while (grid[line][col] == ' ' && line + 2 <= TOTAL_LINE - 2)
		line += 2;
	if(grid[line][col] != ' ')
		line -= 2;
	coordon.x = col;
	coordon.y = line;
	return (coordon);
}

/*----------------------------------------------------------------------------------------*/

void			grid_temp(char grid[][TOTAL_COL], char tmp_grid[][TOTAL_COL])
{	
	create_grid(tmp_grid);
	for(int i = 1; i < TOTAL_LINE; i += 2)
	{
		for(int j = 2; j < TOTAL_COL; j += 4)
		{
			tmp_grid[i][j] = grid[i][j];
			if(grid[i][j] == 'X' || grid[i][j] == 'O')
				grid[i][j] = ' ';
		}
	}
}

/*----------------------------------------------------------------------------------------*/

void			inverse_grid(char grid[][TOTAL_COL])
{
	char		tmp_grid[TOTAL_LINE][TOTAL_COL];
	coord		cord1;
	coord		cord2;
	char		sig;

	grid_temp(grid,tmp_grid);
	for(int i = 1; i < TOTAL_LINE; i += 2)
	{
		for(int j = 2; j < TOTAL_COL; j += 4)
		{	
			sig = tmp_grid[i][j];
			if(sig == 'X' || sig == 'O')
			{
				cord1.x = j;
				cord1.y = 1;
				cord2 = deplace_jeton(grid,cord1);
				grid[cord2.y][cord2.x] = sig;
			}
		}
	}
}

/*----------------------------------------------------------------------------------------*/

void			inverse_grid_left(char grid[][TOTAL_COL])
{
	char		tmp_grid[TOTAL_LINE][TOTAL_COL];
	coord		cord1;
	coord		cord2;
	char		sig;

	grid_temp(grid, tmp_grid);
	for (int i = 2; i < TOTAL_COL; i += 4)
	{
		for(int j = 1; j < TOTAL_LINE; j += 2)
		{
			sig = tmp_grid[j][i];
			if(sig == 'X' || sig == 'O')
			{
				cord1.x = j * 2;
				cord1.y = 1;
				cord2 = deplace_jeton(grid,cord1);
				grid[cord2.y][cord2.x] = sig;
			}
		}
	}
}

/*----------------------------------------------------------------------------------------*/

void			inverse_grid_right(char grid[][TOTAL_COL])
{
	char		tmp_grid[TOTAL_LINE][TOTAL_COL];
	coord		cord1;
	coord		cord2;
	char		sig;

	grid_temp(grid,tmp_grid);
	for (int i = TOTAL_COL - 3; i >= 2; i -= 4)
	{
		for(int j = TOTAL_LINE - 2; j >= 1; j -= 2)
		{
			sig = tmp_grid[j][i];
			if(sig == 'X' || sig == 'O')
			{
				cord1.x = ((TOTAL_LINE - 1) - j) * 2;
				cord1.y = 1;
				cord2 = deplace_jeton(grid,cord1);
				grid[cord2.y][cord2.x] = sig;
			}
		}
	}
}

/*----------------------------------------------------------------------------------------*/

void			save_game(char grid[][TOTAL_COL], ind_nb_joueur indNbrJr)
{
	FILE		*fic;
	char		name[13];
	char		car1;
	char		car2;

	while (true)
	{
		fflush(stdin);
		printf("Voulez-vous quitter ? [y/n] : ");
		car1 = getchar();
		if (car1 == 'n')
			return;
		else if (car1 == 'y')
		{
			while (true)
			{
				fflush(stdin);
				printf("Voulez-vous sauvegarder la partie ? [y/n] : ");
				car2 = getchar();
				if (car2 == 'y')
				{
					do
					{
						fflush(stdin);
						printf("Veuillez choisir Nom du fichier [10 caractères max] : ");
						fgets(name,13, stdin);
						if (!(fic = fopen(name,"r")) && (strlen(name) < 12))
						{
							name[strlen(name)] = '~';
							create_file(grid, indNbrJr, name);
							exit(EXIT_SUCCESS);
						}
						else
							printf("Nom Existe déjà, ou trop long.\n");
						fclose(fic);
						
					} while (true);
				}
				else if (car2 == 'n')
					exit(EXIT_SUCCESS);
				printf("(y) --> quit avec sauvegarde, (n) --> quit sans sauvegarde\n");
			}
		}
		else
			printf("(y) --> Quitter / (n) --> Continuer\n");
	}
}

/*----------------------------------------------------------------------------------------*/

coord		check_inversion(char grid[][TOTAL_COL])
{
	coord	cordon;
	coord	cord;
	int		cmpt1 = 0;
	int		cmpt2 = 0;
	
	cord.x = 0;
	cord.y = 0;
	cordon.y = 1;
	while (cordon.y < TOTAL_LINE - 1)
	{
		cordon.x = 2;
		while (cordon.x < TOTAL_COL - 2)
		{
			if (grid[cordon.y][cordon.x] != ' ')
			{
				if (check_jeu(grid, cordon))
				{
					if (grid[cordon.y][cordon.x] == 'X')
						cmpt1 = 1;
					else if(grid[cordon.y][cordon.x] == 'O')
						cmpt2 = 1;
					cord = cordon;
				}
			}
			cordon.x += 4;
		}
		cordon.y += 2;
	}
	if (cmpt1 == 1 && cmpt2 == 1)
	{
		cord.x = 1;
		cord.y = 1;
	}
	return (cord);
}

/*----------------------------------------------------------------------------------------*/

coord			check_pos(coord point, char choi_col, char grid[][TOTAL_COL], ind_nb_joueur indNbrJr, char *sig)
{
	coord           coordonnees;

	coordonnees.x = 0;
	coordonnees.y = 0;
	switch (coordonne(choi_col))
	{
		case -1:
			printf("\nNuméro de case invalide!!!\n\n");
			return (coordonnees);
		case 0:
			inverse_grid(grid);
			coordonnees = check_inversion(grid);
			*indNbrJr.indJr *= -1 ;
			return (coordonnees);
		case 8:
			inverse_grid_left(grid);
			coordonnees = check_inversion(grid);
			*indNbrJr.indJr *= -1 ;
			return (coordonnees);
		case 9:
			inverse_grid_right(grid);
			coordonnees = check_inversion(grid);
			*indNbrJr.indJr *= -1 ;
			return (coordonnees);
	}
	if (coordonne(choi_col) == -2)
		save_game(grid, indNbrJr);
	else if (grid[point.y][point.x] != ' ')
		printf("\nColonne pleine, Veuillez choisir une autre colonne.\n\n");
	else
	{
		coordonnees = deplace_jeton(grid, point);
		grid[coordonnees.y][coordonnees.x] = *sig;
		*indNbrJr.indJr *= -1 ;
	}
	return (coordonnees);
}
/*----------------------------------------------------------------------------------------*/

void			affiche_gagnant(ind_nb_joueur indNbrJr)
{
	if (indNbrJr.nbJr == '2')
	{
		if (*indNbrJr.indJr == -1)
			printf("\n\t------- Bravo Joueur 1 a gagné!!! -------\n\n");
		else
			printf("\n\t------- Bravo Joueur 2 a gagné!!! -------\n\n");
	}
	else if (indNbrJr.nbJr == '1')
	{
		if (*indNbrJr.indJr == -1)
			printf("\n\t------- Bravo vous avez gagné!!! -------\n\n");
		else
			printf("\n\t------- Dommage vous avez perdu!!! -------\n\n");
	}
	else
	{
		if (*indNbrJr.indJr == -1)
			printf("\n\t------- Bravo IA_1 a gagné!!! -------\n\n");
		else
			printf("\n\t------- Bravo IA_2 a gagné!!! -------\n\n");
	}
	
}

/*----------------------------------------------------------------------------------------*/

void			lancer_jeu_2_joueurs(char grid[][TOTAL_COL], ind_nb_joueur indNbrJr)
{
	int			cmpt;
	char		symbol;
	char		choi_col;
	coord		cur_coord;
	coord		point_coord;
	
	cmpt = 0;
	while (true)
	{
		affiche_grid(grid);
		check_joueur(indNbrJr, &symbol);
		fflush(stdin);
		choi_col = getchar();
		point_coord.y = 1;
		point_coord.x = coordonne(choi_col);
		cur_coord = check_pos(point_coord, choi_col, grid, indNbrJr, &symbol);
		if (cur_coord.y == 0 && cur_coord.x == 0)
			continue;
		if (cur_coord.y == 1)
			cmpt++;
		if (check_jeu(grid, cur_coord) && (cur_coord.y != 1 || cur_coord.x != 1))
			break ;
		if(cmpt == 7 || (cur_coord.y == 1 && cur_coord.x == 1))
		{
			affiche_grid(grid);
			printf("\n\t-------Partie terminée, match null!!!-------\n\n");
			return ;
		}
	}
	affiche_grid(grid);
	affiche_gagnant(indNbrJr);
	return ;		
}

/*----------------------------------------------------------------------------------------*/

int			check_col(char grid[][TOTAL_COL], coord cord)
{
	int		posit_x;
	int		posit_y;
	int		i;

	posit_x = cord.x;
	posit_y = cord.y;
	i = 1;
	while (i <= 4)
	{
		if (posit_y == TOTAL_LINE - 2)
			return (i);
		if (grid[posit_y][posit_x] != grid[posit_y + 2][posit_x])
			return (i);
		posit_y += 2;
		i++;
	}
	return (i);
}

/*----------------------------------------------------------------------------------------*/

int			check_line_left(char grid[][TOTAL_COL], coord cord)
{
	int		cmpt;

	cmpt = 0;
	if (cord.x == 2)
		return (cmpt);
	while (cord.x >= 6)
	{
		if (grid[cord.y][cord.x] == grid[cord.y][cord.x - 4])
			cmpt++;
		else
			return(cmpt);
		cord.x -= 4;
	}
	return (cmpt);
}

/*----------------------------------------------------------------------------------------*/

int				check_line_right(char grid[][TOTAL_COL], coord cord)
{
	int			cmpt;

	cmpt = 0;
	if (cord.x == TOTAL_COL - 3)
		return (cmpt);
	while (cord.x <= 22)
	{
		if (grid[cord.y][cord.x] == grid[cord.y][cord.x + 4])
			cmpt++;
		else
			return(cmpt);
		cord.x += 4;
	}
	return (cmpt);
}

/*----------------------------------------------------------------------------------------*/

bool			check_row(int value_left, int value_right)
{
	if(value_left + value_right == 3)
		return(true);
	return(false);
}

/*----------------------------------------------------------------------------------------*/

int			check_diag_left_up(char grid[][TOTAL_COL], coord cord)
{
	int		cmpt;

	cmpt = 0;
	if (cord.x == 2 || cord.y == 1)
		return (cmpt);
	while (cord.x >= 6 && cord.y >= 3)
	{
		if (grid[cord.y][cord.x] == grid[cord.y - 2][cord.x - 4])
			cmpt++;
		else
			return(cmpt);
		cord.x -= 4;
		cord.y -= 2;
	}
	return (cmpt);
}

/*----------------------------------------------------------------------------------------*/

int			check_diag_left_down(char grid[][TOTAL_COL], coord cord)
{
	int		cmpt;

	cmpt = 0;
	if (cord.x == TOTAL_COL - 3 || cord.y == TOTAL_LINE - 2)
		return (cmpt);
	while (cord.x <= 22 && cord.y <= 11)
	{
		if (grid[cord.y][cord.x] == grid[cord.y + 2][cord.x + 4])
			cmpt++;
		else
			return(cmpt);
		cord.x += 4;
		cord.y += 2;
	}
	return (cmpt);
}

/*----------------------------------------------------------------------------------------*/

int			check_diag_right_up(char grid[][TOTAL_COL], coord cord)
{
	int		cmpt;
	
	cmpt = 0;
	if (cord.x == TOTAL_COL - 3 || cord.y == 1)
		return (cmpt);
	while (cord.x <= 22 && cord.y >= 3)
	{
		if (grid[cord.y][cord.x] == grid[cord.y - 2][cord.x + 4])
			cmpt++;
		else
			return (cmpt);
		cord.x += 4;
		cord.y -= 2;
	}
	return (cmpt);
}

/*----------------------------------------------------------------------------------------*/

int			check_diag_right_down(char grid[][TOTAL_COL], coord cord)
{
	int		cmpt;

	cmpt = 0;
	if (cord.x == 2 || cord.y == TOTAL_LINE - 2)
		return (cmpt);
	while (cord.x >= 6 && cord.y <= 11)
	{
		if (grid[cord.y][cord.x] == grid[cord.y + 2][cord.x - 4])
			cmpt++;
		else
			return (cmpt);
		cord.x -= 4;
		cord.y += 2;
	}
	return (cmpt);
}

/*----------------------------------------------------------------------------------------*/

bool		check_diag_left(int value_up, int value_down)
{
	if (value_up + value_down >= 3)
		return (true);
	return (false);
}

/*----------------------------------------------------------------------------------------*/

bool		check_diag_right(int value_up, int value_down)
{
	if (value_up + value_down >= 3)
		return (true);
	return (false);
}

/*----------------------------------------------------------------------------------------*/

bool		check_jeu(char grid[][TOTAL_COL], coord cord)
{
	if ((check_col(grid, cord) == 4))
		return (true);
	if (check_row(check_line_left(grid, cord), check_line_right(grid, cord)))
		return (true);
	if (check_diag_left(check_diag_left_up(grid, cord), check_diag_left_down(grid, cord)))
		return (true);
	if (check_diag_right(check_diag_right_up(grid,cord), check_diag_right_down(grid, cord)))
		return (true);
	return (false);
}

/*----------------------------------------------------------------------------------------*/

int			check_row_IA(int value_left, int value_right)
{
	return (value_left + value_right);
}

/*----------------------------------------------------------------------------------------*/

int			check_diag_left_IA(int value_up, int value_down)
{
	return (value_up + value_down);
}

/*----------------------------------------------------------------------------------------*/

int			check_diag_right_IA(int value_up, int value_down)
{
	return (value_up + value_down);
}

/*----------------------------------------------------------------------------------------*/

int			value_col(char grid[][TOTAL_COL], coord cord)
{
	int		max;
	int		tab[4];

	tab[0] = check_col(grid, cord);
	tab[1] = check_row_IA(check_line_left(grid, cord), check_line_right(grid, cord)) + 1;
	tab[2] = check_diag_left_IA(check_diag_left_up(grid, cord), check_diag_left_down(grid, cord)) + 1;
	tab[3] = check_diag_right_IA(check_diag_right_up(grid,cord), check_diag_right_down(grid, cord)) + 1;
	max = tab[0];
	for(int i = 1; i < 4; i++)
		if (max < tab[i])
			max = tab[i];
	return (max);
}
/*----------------------------------------------------------------------------------------*/

result		jeu_gagnant_IA(char grid[][TOTAL_COL], coord cord, char *sign)
{
	result	s_val;
	int		index;
	int		tab[7];
	coord	cordon;
	
	index = -1;
	s_val.num_col = 0;
	s_val.val_max = 0;
	while (cord.x < TOTAL_COL - 2)
	{
		index++;
		cord.y = 1;
		if (grid[cord.y][cord.x] != ' ')
		{
			cord.x += 4;
			continue;
		}
		cordon = deplace_jeton(grid, cord);
		grid[cordon.y][cordon.x] = *sign;
		tab[index] = value_col(grid, cordon);
		grid[cordon.y][cordon.x] = ' ';
		if (s_val.val_max < tab[index])
		{
			s_val.num_col = index;
			s_val.val_max = tab[index];
		}
		cord.x += 4;
	}	
	return (s_val);
}

/*----------------------------------------------------------------------------------------*/

result		jeu_perdant_IA(char grid[][TOTAL_COL], coord cord, char sign)
{
	result	s_val;
	int		index;
	int		tab[7];
	coord	cordon;

	index = -1;
	s_val.num_col = 0;
	s_val.val_max = 0;
	while (cord.x < TOTAL_COL - 2)
	{
		index++;
		cord.y = 1;
		if (grid[cord.y][cord.x] != ' ')
		{
			cord.x += 4;
			continue;
		}
		cordon = deplace_jeton(grid, cord);
		grid[cordon.y][cordon.x] = sign;
		tab[index] = value_col(grid, cordon);
		grid[cordon.y][cordon.x] = ' ';
		if (s_val.val_max < tab[index])
		{
			s_val.num_col = index;
			s_val.val_max = tab[index];
		}
		cord.x += 4;
	}
	return (s_val);
}

/*----------------------------------------------------------------------------------------*/

coord		jeu_IA(char grid[][TOTAL_COL], char col, coord cord, coord point, ind_nb_joueur indNbrJr, char *sig)
{
	char	tab[2];
	result	gagnant;
	result	perdant;
	int		colonne;
	char	symb_advers;

	point.x = 2;
	point.y = 1;
	symb_advers = (*indNbrJr.indJr == 1) ? 'X' : 'O';
	gagnant = jeu_gagnant_IA(grid, point, sig);
	perdant = jeu_perdant_IA(grid, point, symb_advers);
	if (gagnant.val_max >= perdant.val_max)
	{
		colonne = gagnant.num_col + 1;
		sprintf(tab,"%d",colonne);
		col = tab[0];
		point.x = coordonne(col);
		cord = check_pos(point, col, grid, indNbrJr, sig);
	}
	else
	{
		colonne = perdant.num_col + 1;
		sprintf(tab,"%d",colonne);
		col = tab[0];
		point.x = coordonne(col);
		cord = check_pos(point, col, grid, indNbrJr, sig);
	}
	return (cord);
}

/*----------------------------------------------------------------------------------------*/

void		lancer_jeu_avec_IA(char grid[][TOTAL_COL], ind_nb_joueur indNbrJr)
{
	int		cmpt;
	char	symbol;
	char	choi_col;
	coord	cur_coord;
	coord	point_coord;
	
	cmpt = 0;
	while (true)
	{
		affiche_grid(grid);
		check_joueur(indNbrJr, &symbol);
		if (*indNbrJr.indJr == 1)
		{
			fflush(stdin);
			choi_col = getchar();
			point_coord.y = 1;
			point_coord.x = coordonne(choi_col);
			cur_coord = check_pos(point_coord, choi_col, grid, indNbrJr, &symbol);
		}
		else
		{
			cur_coord = jeu_IA(grid, choi_col, cur_coord, point_coord, indNbrJr, &symbol);
		}
		if (cur_coord.y == 0 && cur_coord.x == 0)
			continue;
		if (cur_coord.y == 1)
			cmpt++;
		if (check_jeu(grid, cur_coord) && (cur_coord.y != 1 || cur_coord.x != 1))
			break ;
		if(cmpt == 7 || (cur_coord.y == 1 && cur_coord.x == 1))
		{
			affiche_grid(grid);
			printf("\n\t-------Partie terminée, match null!!!-------\n\n");
			return ;
		}
	}
	affiche_grid(grid);
	affiche_gagnant(indNbrJr);
	return ;
}

/*----------------------------------------------------------------------------------------*/

void		lancer_jeu_IA_Seul(char grid[][TOTAL_COL], ind_nb_joueur indNbrJr)
{
	int		cmpt;
	int		colone;
	char	symbol;
	char	choi_col = '\0';
	coord	cur_coord;
	coord	point_coord;
	int		tab[] = {2, 6, 10, 14, 18, 22, 26};
	
	cmpt = 0;
	cur_coord.x = 0; 
	cur_coord.y = 0;
	srand( time( NULL ) );
	colone = rand() % 6;
	point_coord.y = 13;
	point_coord.x = tab[colone];
	grid[point_coord.y][point_coord.x] = '0';
	*indNbrJr.indJr *= -1;
	
	while (true)
	{
		printf("\n");
		affiche_grid(grid);
		check_joueur(indNbrJr, &symbol);
		sleep(1);
		
		cur_coord = jeu_IA(grid, choi_col, cur_coord, point_coord, indNbrJr, &symbol);
		
		if (cur_coord.y == 0 && cur_coord.x == 0)
			continue;
		if (cur_coord.y == 1)
			cmpt++;
		if (check_jeu(grid, cur_coord) && (cur_coord.y != 1 || cur_coord.x != 1))
			break ;
		if(cmpt == 7 || (cur_coord.y == 1 && cur_coord.x == 1))
		{
			affiche_grid(grid);
			printf("\n\t-------Partie terminée, match null!!!-------\n\n");
			return ;
		}
	}
	printf("\n");
	affiche_grid(grid);
	affiche_gagnant(indNbrJr);
	return ;
}

/*----------------------------------------------------------------------------------------*/

void		create_file(char grid[][TOTAL_COL], ind_nb_joueur indNbrJr, char choi_nom[])
{
	FILE	*fichier;
	char	indice;

	if (!(fichier = fopen(choi_nom, "a")))
	{
		printf("Echec de sauvegarde!!!\n");
		return ;
	}
	indice = *indNbrJr.indJr;
	fprintf(fichier, "%d",indice);
	fputc(' ',fichier);
	fputc(indNbrJr.nbJr,fichier);
	for( int i = 0; i < TOTAL_LINE; i++)
		for(int j = 0; j < TOTAL_COL; j++)
			fputc(grid[i][j],fichier);

	fclose(fichier);
}

/*----------------------------------------------------------------------------------------*/

ind_nb_joueur		restaure_jeu(FILE * fich, char grid[][TOTAL_COL])
{
	ind_nb_joueur	indiceNbrJoueur;

	if (fich == NULL )
	{
		printf("Echec d'ouverture, fichier introuvable!!!\n");
		exit(EXIT_FAILURE);
	}
	fscanf(fich, "%d", indiceNbrJoueur.indJr);
	fseek(fich, 1, SEEK_CUR);
	indiceNbrJoueur.nbJr = fgetc(fich);
	for( int i = 0; i < TOTAL_LINE; i++)
		for(int j = 0; j < TOTAL_COL; j++)
			grid[i][j] = fgetc(fich);
	return (indiceNbrJoueur);
}

/*----------------------------------------------------------------------------------------*/

bool		partie_sauv()
{
	DIR * dir;
	if ((dir = opendir(".")) == NULL)
    	return (EXIT_FAILURE);
	struct dirent *fich;
	while ((fich = readdir(dir)))
	{
		if(fich->d_name[strlen(fich->d_name) - 1] == '~')
		{
			closedir(dir);
			return (true);
		}
	} 
    closedir(dir);
	return (false);
}

/*----------------------------------------------------------------------------------------*/

bool		check_directory(char name[])
{
	DIR * dir;
	if ((dir = opendir(".")) == NULL)
    	return (EXIT_FAILURE);
	struct dirent *fich;
	while ((fich = readdir(dir)))
	{
		if(strcmp(fich->d_name,name))
		{
			closedir(dir);
			return (true);
		}		
	}
    closedir(dir);
	return (false);
}

/*----------------------------------------------------------------------------------------*/

void		restart_game(char grid[][TOTAL_COL], ind_nb_joueur indiceNb_joueur, char name[])
{
	FILE	* fich = NULL;
	int		indice;
	
	fich = fopen(name, "r");
	printf("\n");
	indiceNb_joueur = restaure_jeu(fich,grid);
	remove(name);
	indice = *indiceNb_joueur.indJr;
	indiceNb_joueur.indJr = &indice;
	if (indiceNb_joueur.nbJr == '2')
	{
		lancer_jeu_2_joueurs(grid, indiceNb_joueur);
		return ;
	}
	else
	{
		lancer_jeu_avec_IA(grid, indiceNb_joueur);
		return ;
	}	
}

/*----------------------------------------------------------------------------------------*/

void		clear_grid(char grid[][TOTAL_COL])
{
	for(int i = 1; i < TOTAL_LINE; i += 2)
		for(int j = 2; j < TOTAL_COL; j += 4)
			grid[i][j] = ' ';
}

/*----------------------------------------------------------------------------------------*/

void		new_game(char grid[][TOTAL_COL], ind_nb_joueur indiceNb_joueur)
{
	while (true)
	{
		fflush(stdin);
		printf("Veuillez saisir le nombre de joueur( 0, 1 ou 2) : ");
		indiceNb_joueur.nbJr = getchar();
		if (indiceNb_joueur.nbJr == '2')
		{
			lancer_jeu_2_joueurs(grid, indiceNb_joueur);
			clear_grid(grid);
			break ;
		}
		else if(indiceNb_joueur.nbJr == '1')
		{
			lancer_jeu_avec_IA(grid, indiceNb_joueur);
			clear_grid(grid);
			break;
		}
		else if(indiceNb_joueur.nbJr == '0')
		{
			lancer_jeu_IA_Seul(grid, indiceNb_joueur);
			clear_grid(grid);
			break;
		}
		else
		{
			printf("Le nombre de joueur doit être 0, 1 ou 2\n");
			continue ;
		}
	}

}

/*----------------------------------------------------------------------------------------*/

void				create_jeu()
{
	char			car;
	char			name[13];
	int				indice;
	char			partie;
	char			grid[TOTAL_LINE][TOTAL_COL];
	ind_nb_joueur	indiceNb_joueur;

	indice = 1;
	indiceNb_joueur.indJr = &indice;
	indiceNb_joueur.nbJr = 0;
	while (true)
	{
		create_grid(grid);
		if (partie_sauv())
		{
			while (true)
			{
				fflush(stdin);
				printf("Voulez-vous continuer une partie ? [y/n] : ");
				car = getchar();
				if (car == 'y')
				{
					printf("Veuillez saisir le nom de votre fichier : ");
					fflush(stdin);
					fgets(name,13, stdin);
					name[strlen(name)] = '~';
					if (check_directory(name))
						restart_game(grid, indiceNb_joueur,name);
				}
				else if (car == 'n')
					break;
				else
					continue;
			}
		}
		while (true)
		{
			new_game(grid, indiceNb_joueur);
			fflush(stdin);
			printf("Nouvelle Partie ? [y/n] : ");
			partie = getchar();
			if (partie == 'n')
				exit(EXIT_SUCCESS);
			else if(partie == 'y')
				break;
			else
				printf("(y) -> nouvelle partie ou (n) -> quitter.\n");
		}
	}
}
