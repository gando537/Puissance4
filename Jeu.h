/************************************************************************
# Text File
# AUTHOR:   Gando
# FILE:     /Users/Gando/Desktop/Projet_P4/prototypes.h
# CREATED:  15:26:45 26/11/2020
# MODIFIED: 15:26:45 26/11/2020
************************************************************************/

#ifndef _JEU_H_
#define _JEU_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

typedef struct	coordonnees
{
	int			x;
	int			y;
}				coord;

typedef struct	result
{
	int			val_max;
	int			num_col;
}				result;

typedef	struct	ind_nb_joueur
{
	int			*indJr;
	char		nbJr;
}				ind_nb_joueur;

#define TOTAL_LINE 15
#define TOTAL_COL 29

void                    put_if(char	grid[][TOTAL_COL], int cond, char vrai, char faux, int x, int y);
void                    affiche_num_col();
void                    affiche_grid(char grid[][TOTAL_COL]);
void                    create_grid();
void                    lancer_jeu_2_joueurs(char grid[][TOTAL_COL], ind_nb_joueur indNbrJr);
void                    lancer_jeu_avec_IA(char grid[][TOTAL_COL], ind_nb_joueur indNbrJr);
void					lancer_jeu_IA_Seul(char grid[][TOTAL_COL], ind_nb_joueur indNbrJr);
int                     coordonne(char num_col);
void                    check_joueur(ind_nb_joueur indNbrJr, char *sign);
void                    affiche_gagnant(ind_nb_joueur indNbrJr);
coord                   deplace_jeton(char grid[][TOTAL_COL], coord coordon);
void                    save_game(char grid[][TOTAL_COL], ind_nb_joueur indNbrJr);
coord					check_inversion(char grid[][TOTAL_COL]);
coord                   check_pos(coord point, char choi_col, char grid[][TOTAL_COL], ind_nb_joueur indNbrJr, char *sig);
int                     check_line_left(char grid[][TOTAL_COL], coord cord);
int                     check_line_right(char grid[][TOTAL_COL], coord cord);
bool                    check_row(int value_left, int value_right);
int                     check_col(char grid[][TOTAL_COL], coord cord);
int						check_diag_left_up(char grid[][TOTAL_COL], coord cord);
int                     check_diag_left_down(char grid[][TOTAL_COL], coord cord);
int						check_diag_right_up(char grid[][TOTAL_COL], coord cord);
int                     check_diag_right_down(char grid[][TOTAL_COL], coord cord);
bool                    check_diag_left(int value_up, int value_down);
bool                    check_diag_right(int value_up, int value_down);
bool					check_jeu(char grid[][TOTAL_COL], coord cord);
void					grid_temp(char grid[][TOTAL_COL],char tmp_grid[][TOTAL_COL]);
void                    inverse_grid(char grid[][TOTAL_COL]);
void                    inverse_grid_left(char grid[][TOTAL_COL]);
void                    inverse_grid_right(char grid[][TOTAL_COL]);
coord					jeu_IA(char grid[][TOTAL_COL], char col, coord cord, coord point, ind_nb_joueur indNbrJr, char *sig);
int						check_row_IA(int value_left, int value_right);
int						check_diag_left_IA(int value_up, int value_down);
int						check_diag_right_IA(int value_up, int value_down);
result					jeu_gagnant_IA(char grid[][TOTAL_COL], coord cord, char *sign);
result					jeu_perdant_IA(char grid[][TOTAL_COL], coord cord, char sign);
bool					partie_sauv();
void					clear_grid(char grid[][TOTAL_COL]);
bool					check_directory(char name[]);
int                     value_col(char grid[][TOTAL_COL], coord cord);
void                    create_file(char grid[][TOTAL_COL], ind_nb_joueur indNbrJr, char choi_nom[]);
ind_nb_joueur           restaure_jeu(FILE * fich, char grid[][TOTAL_COL]);
void                    restart_game(char grid[][TOTAL_COL], ind_nb_joueur indiceNb_joueur, char name[]);
void                    new_game(char grid[][TOTAL_COL], ind_nb_joueur indiceNb_joueur);

#endif
