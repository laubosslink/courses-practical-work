#ifndef INCLUDED_H_M_ADJ
#define INCLUDED_H_M_ADJ

#include <lifo.h>

typedef struct m_adj* m_adj;

m_adj m_adj_load_file(char* filename);

Lifo m_adj_pred(m_adj matrice, int sommet);

int m_adj_max(int n1, int n2);

int m_adj_min(int n1, int n2);

m_adj m_adj_init(int length);

int m_adj_get_file_duration(char* filename, int sommet);

int m_adj_get_duration(m_adj m, int sommet);

int m_adj_get_duration_from_to(m_adj m, int sommet_from, int sommet_to);

int m_adj_dtot(m_adj m, int sommet);

void m_adj_date_plus_tard(char* filename, char *filename_topo, m_adj m);

void m_adj_date_plus_tot(char* filename, char *filename_topo, m_adj m);

int m_adj_max(int n1, int n2);

char* m_adj_get_tache(char* filename, int sommet);

int m_adj_dtard(m_adj m, int sommet);

int m_adj_get_sommet(char* filename, char* nom_tache);

#endif
