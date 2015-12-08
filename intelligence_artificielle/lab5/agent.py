#! /usr/bin/python
# -*- coding: utf-8; mode: python -*-
#
# ENSICAEN
# École Nationale Supérieure d'Ingénieurs de Caen
# 6 Boulevard Maréchal Juin
# F-14050 Caen Cedex France
#
# Artificial Intelligence 2I1AE1
#

#
# @file agents.py
#
# @author Régis Clouard.
#

#
# @author ELHIMDI Yasmine
# @author PARMENTIER Laurent
#

import random
import copy
import utils

#affichage
DEBUG=True

# CASES
VISITE=0
PAS_VISITE=1
PAS_DANGEREUX=2
HYPOTHESE_PUIT=3
WAMPUS=4
OR=5
MUR=9

# ORIENTATIONS
DROITE=0
BAS=1
GAUCHE=2
HAUT=3

class Agent:
    """
    The base class for various flavors of the agent.
    This an implementation of the Strategy design pattern.
    """
    def think( self, percept ):
        raise Exception, "Invalid Agent class, think() not implemented"

    def init( self, gridSize ):
        raise Exception, "Invalid Agent class, init() not implemented"

class DummyAgent( Agent ):
    """
    An example of simple Wumpus hunter brain: acts randomly...
    """

    def init( self, gridSize ):
        pass

    def think( self, percept ):
        return random.choice(['shoot', 'grab', 'left', 'right', 'forward', 'forward'])

#######
####### Exercise 1: Goal-Based Agent
#######
class GoalBasedAgent( Agent ):
    """
    Your smartest Wumpus hunter brain.
    """
    action = ['right', 'forward', 'forward', 'forward', 'forward', 'forward', 'forward', 'left', 'forward']
    force_action = []
    win_action = []

    grid = []

    stench_mode = False
    action_t_mode_mur = False
    wumpus_est_mort = False

    or_attrape = False

    force_puit_mode = False

    position_joueur = [1, 1] # position initale : ligne, colonne
    orientation = DROITE # 0 droite, 1 bas, 2 gauche, 3 haut

    gridSize = 0

    def init( self, gridSize ):
        self.gridSize = gridSize
        for i in range(0, gridSize):
          for j in range(0, gridSize):
            if i == 0 or j == 0 or i == gridSize-1 or j == gridSize-1:
              self.grid.append([MUR])
            else:
              self.grid.append([PAS_VISITE])

    def index_case(self, ligne, colonne):
      return ligne*self.gridSize + colonne

    def case(self, ligne, colonne):
      return self.grid[self.index_case(ligne, colonne)]

    def memoire_tourner_droite(self):
        self.orientation = ((self.orientation + 1) % 4)

    def memoire_tourner_gauche(self):
      self.orientation = (self.orientation - 1)

      if self.orientation < 0:
        self.orientation = 3

    def memoire_avancer(self):
        ligne, colonne = self.position_joueur # @todo bug position joueur fausse, car il forward dans un mur..

        if PAS_VISITE in self.case(ligne, colonne):
          self.grid[self.index_case(ligne, colonne)] = [VISITE]

        if PAS_DANGEREUX not in self.case(ligne, colonne):
          self.grid[self.index_case(ligne, colonne)] += [PAS_DANGEREUX]

        if self.orientation == DROITE:
          if MUR not in self.case(ligne, colonne + 1):
            self.position_joueur = [ligne, colonne + 1]
        elif self.orientation == BAS:
          if MUR not in self.case(ligne + 1, colonne):
            self.position_joueur = [ligne + 1, colonne]
        elif self.orientation == GAUCHE:
          if MUR not in self.case(ligne, colonne - 1):
            self.position_joueur = [ligne, colonne - 1]
        elif self.orientation == HAUT:
          if MUR not in self.case(ligne - 1, colonne):
            self.position_joueur = [ligne - 1, colonne]

    def avancer( self ):
        self.memoire_avancer()
        self.action += ['forward']

    def action_smart( self, action ):
        if action == 'forward':
          self.memoire_avancer()
        elif action == 'right':
          self.memoire_tourner_droite()
        elif action == 'left':
          self.memoire_tourner_gauche()
        return action

    def actions_pour_se_diriger_direction( self, diriger_direction ):
        difference = diriger_direction - self.orientation
        difference = abs(difference)

        if difference == 0:
          return []
        elif difference == 2:
            return ['right', 'right']
        else: # @todo peut on optimise ?
          if self.orientation == DROITE and diriger_direction == BAS:
            return ['right']
          elif self.orientation == BAS and diriger_direction == GAUCHE:
            return ['right']
          elif self.orientation == GAUCHE and diriger_direction == HAUT:
            return ['right']
          elif self.orientation == HAUT and diriger_direction == DROITE:
            return ['right']
          else:
            return ['left']

    def actions_pour_aller_orientation( self, orientation):
        actions = self.actions_pour_se_diriger_direction(orientation)
        actions.append('forward')
        return actions

    def index_case_pour_aller_orientation( self, orientation ):
        return self.index_case_pour_actions(self.actions_pour_aller_orientation(orientation))

    def orientation_oppose( self, orientation=None ):
        if not orientation:
          orientation = self.orientation

        return (orientation + 2) % 4

    def direction_oppose( self, direction ):
        if direction == 'right':
          return 'left'
        else: # direction == left
          return 'right'

    def mur_existe_pour_aller_orientation(self, orientation, actions=None):
        if actions:
            return MUR in self.case_pour_actions(actions + self.actions_pour_aller_orientation(orientation))
        else:
            return MUR in self.case_pour_actions(self.actions_pour_aller_orientation(orientation))

    def ajout_hypothese_puit( self ):
        added=False

        position_devant_agent = self.index_case_pour_aller_orientation(self.orientation)
        position_droite_agent = self.index_case_pour_aller_orientation((self.orientation + 1) % 4)
        position_gauche_agent = self.index_case_pour_aller_orientation((self.orientation - 1) % 4)

        if MUR not in self.grid[position_devant_agent]:
            if HYPOTHESE_PUIT not in self.grid[position_devant_agent]:
                if VISITE not in self.grid[position_devant_agent]:
                  if PAS_DANGEREUX not in self.grid[position_devant_agent]:
                    added = True
                    self.grid[position_devant_agent] += [HYPOTHESE_PUIT]

        if MUR not in self.grid[position_gauche_agent]:
            if HYPOTHESE_PUIT not in self.grid[position_gauche_agent]:
                if VISITE not in self.grid[position_gauche_agent]:
                  if PAS_DANGEREUX not in self.grid[position_gauche_agent]:
                    added = True
                    self.grid[position_gauche_agent] += [HYPOTHESE_PUIT]

        if MUR not in self.grid[position_droite_agent]:
            if HYPOTHESE_PUIT not in self.grid[position_droite_agent]:
                if VISITE not in self.grid[position_droite_agent]:
                  if PAS_DANGEREUX not in self.grid[position_droite_agent]:
                    added = True
                    self.grid[position_droite_agent] += [HYPOTHESE_PUIT]

        return added

    def ajout_actions_demi_tour(self):
        self.action += [ 'right', 'right', 'forward' ]

    def score_actions(self, actions):
      score = 0

      cp_actions = copy.deepcopy(actions)

      grid = copy.deepcopy(self.grid)
      orientation = copy.deepcopy(self.orientation)
      position_joueur = copy.deepcopy(self.position_joueur)

      ligne, colonne = position_joueur

      while cp_actions:
        currentAction = cp_actions.pop(0)

        # gestion de l'orientation
        if currentAction == 'left':
          orientation = orientation - 1
          if orientation < 0:
            orientation = 3
          score = score - 10
        elif currentAction == 'right':
          orientation = (orientation + 1) % 4
          score = score - 10
        elif currentAction == 'forward':

          # maj de la position de l'agent
          if orientation == DROITE:
            if MUR not in grid[self.index_case(ligne, colonne + 1)]:
              position_joueur = [ligne, colonne + 1]
            else:
              score = score - 2000
          elif orientation == BAS:
            if MUR not in grid[self.index_case(ligne + 1, colonne)]:
              position_joueur = [ligne + 1, colonne]
            else:
              score = score - 2000
          elif orientation == GAUCHE:
            if MUR not in grid[self.index_case(ligne, colonne - 1)]:
              position_joueur = [ligne, colonne - 1]
            else:
              score = score - 2000
          elif orientation == HAUT:
            if MUR not in grid[self.index_case(ligne - 1, colonne)]:
              position_joueur = [ligne - 1, colonne]
            else:
              score = score - 2000

          # quel score pour cette position ?
          ligne, colonne = position_joueur
          case = grid[self.index_case(ligne, colonne)]

          if HYPOTHESE_PUIT in case:
            score = score - 1000

          if PAS_DANGEREUX in case:
            score = score + 200

          if PAS_VISITE in case:
            score = score + 300

          elif VISITE in case:
            score = score + 100

      return score

    def adapter_score_pour_file_priorite(self, score):
      return score * -1

    def actions_successeurs( self, actions=None ):
      liste_actions = []

      if MUR not in self.case_pour_actions(['forward'] if not actions else actions + ['forward']):
        liste_actions += [['forward'] if not actions else actions + ['forward']]

      if MUR not in self.case_pour_actions(['right', 'forward'] if not actions else actions + ['right', 'forward']):
        liste_actions += [['right', 'forward'] if not actions else actions + ['right', 'forward']]

      if MUR not in self.case_pour_actions(['right', 'right', 'forward'] if not actions else actions + ['right', 'right', 'forward']):
        liste_actions += [['right', 'right', 'forward'] if not actions else actions + ['right', 'right', 'forward']]

      if MUR not in self.case_pour_actions(['left', 'forward'] if not actions else actions + ['left', 'forward']):
        liste_actions += [['left', 'forward'] if not actions else actions + ['left', 'forward']]

      return liste_actions

    def ucs( self, profondeur=3 ):
      file_priorite = utils.PriorityQueue() # file priorite avec actions

      for actions in self.actions_successeurs():
          priorite = self.adapter_score_pour_file_priorite(self.score_actions(actions))
          file_priorite.push(actions, priorite)
          self.ucs_recursive(actions, file_priorite, profondeur-1)

      meilleurs_actions = file_priorite.pop()[1]

      return meilleurs_actions

    def ucs_recursive( self, prev_actions, file_priorite, profondeur ):
      if profondeur == 0:
        return

      for actions in self.actions_successeurs(prev_actions):
          priorite = self.adapter_score_pour_file_priorite(self.score_actions(actions))
          file_priorite.push(actions, priorite)
          self.ucs_recursive(actions, file_priorite, profondeur-1)

    def index_case_pour_actions(self, actions, position_joueur=None):
        cp_actions = copy.deepcopy(actions)
        orientation = copy.deepcopy(self.orientation)

        if not position_joueur:
          position_joueur = copy.deepcopy(self.position_joueur)

        ligne, colonne = position_joueur

        while cp_actions:
          currentAction = cp_actions.pop(0)

          # gestion de l'orientation
          if currentAction == 'left':
            orientation = orientation - 1
            if orientation < 0:
              orientation = 3
          elif currentAction == 'right':
            orientation = (orientation + 1) % 4

          # si on se deplace, maj de la grille
          elif currentAction == 'forward':
              if orientation == DROITE:
                colonne += 1
              elif orientation == BAS:
                ligne += 1
              elif orientation == GAUCHE:
                colonne -= 1
              elif orientation == HAUT:
                ligne -= 1

        return self.index_case(ligne, colonne)

    def position_case_pour_actions( self, actions ):
        index = self.index_case_pour_actions(actions)
        position = [ index / self.gridSize , index % self.gridSize ]
        return position

    def case_pour_actions(self, actions, position_joueur=None):
        return self.grid[self.index_case_pour_actions(actions, position_joueur)]

    def affiche_grille( self ):
        for i in range(0, self.gridSize):
          cases = []
          for j in range(0, self.gridSize):
              cases.append(self.grid[self.index_case(i, j)])
          print cases


    def mur_haut( self ):
        return MUR in self.case(self.position_joueur[0] - 1 , self.position_joueur[1])

    def mur_droite( self ):
        return MUR in self.case(self.position_joueur[0] , self.position_joueur[1] + 1 )

    def mur_bas( self ):
        return MUR in self.case(self.position_joueur[0] + 1 , self.position_joueur[1])

    def mur_gauche( self ):
        return MUR in self.case(self.position_joueur[0], self.position_joueur[1] - 1)

    def T_actions(self):
        #demi tour
        actions = ['right', 'right', 'forward']

        self.action_t_mode_mur = self.mur_gauche() or self.mur_droite() or self.mur_bas() or self.mur_haut()

        # voir compte rendu
        cas_1 = ((self.mur_haut() and self.orientation == GAUCHE)
                or (self.mur_droite() and self.orientation == HAUT)
                or (self.mur_bas() and self.orientation == DROITE)
                or (self.mur_gauche() and self.orientation == BAS))

        cas_2 = ((self.mur_haut() and self.orientation == DROITE)
                or (self.mur_droite() and self.orientation == BAS)
                or (self.mur_bas() and self.orientation == GAUCHE)
                or (self.mur_gauche() and self.orientation == HAUT))

        if cas_1: # orientation == HAUT ou DROITE
          # cote 1
          actions += ['right', 'forward', 'right' ]

          # retour initial
          actions += ['right', 'forward', 'left', 'forward']
        elif cas_2:
          # cote
          actions += ['left', 'forward', 'left' ]

          # retour initial
          actions += ['left', 'forward', 'right', 'forward']
        else:
          # cote 1
          actions += ['left', 'forward', 'left']

          # cote 2
          actions += ['left', 'forward', 'forward', 'right']

          # retour initial
          actions += ['right', 'forward', 'left', 'forward']

        return actions

    def ajout_T_actions( self ):
        self.action += self.T_actions()

    def perception_danger( self, percept ):
      return percept.breeze or percept.stench

    def ajout_case_voisines_sans_danger( self ):
      for actions in self.actions_successeurs():
        if PAS_DANGEREUX not in self.grid[self.index_case_pour_actions(actions)]:
          self.grid[self.index_case_pour_actions(actions)] += [PAS_DANGEREUX]
          if HYPOTHESE_PUIT in self.grid[self.index_case_pour_actions(actions)]:
            self.grid[self.index_case_pour_actions(actions)].remove(HYPOTHESE_PUIT)

    def actions_successeurs_visite( self, actions=None ):
      liste_actions = []

      if VISITE in self.case_pour_actions(['forward'] if not actions else actions + ['forward']):
        liste_actions += [['forward'] if not actions else actions + ['forward']]

      if VISITE in self.case_pour_actions(['right', 'forward'] if not actions else actions + ['right', 'forward']):
        liste_actions += [['right', 'forward'] if not actions else actions + ['right', 'forward']]

      if VISITE in self.case_pour_actions(['right', 'right', 'forward'] if not actions else actions + ['right', 'right', 'forward']):
        liste_actions += [['right', 'right', 'forward'] if not actions else actions + ['right', 'right', 'forward']]

      if VISITE in self.case_pour_actions(['left', 'forward'] if not actions else actions + ['left', 'forward']):
        liste_actions += [['left', 'forward'] if not actions else actions + ['left', 'forward']]

      return liste_actions
    

    def actions_retour_case_depart( self ):
        stack = self.actions_successeurs_visite()
        visited = []

        return ['right', 'forward', 'left', 'shoot', 'left', 'forward', 'forward', 'forward', 'right', 'forward', 'forward']

        while stack:
          actions = stack.pop()
          #print "actions: " + str(actions)
          current_case = self.case_pour_actions(actions)
          if self.index_case_pour_actions(actions) == (self.gridSize + 1):
            return actions
          elif current_case not in visited:
            visited += [actions]
            next_actions_succ = self.actions_successeurs_visite(actions)
            #print "successeurs: " + str(next_actions_succ)
            for next_actions in next_actions_succ:
              if next_actions not in visited:
                stack.append(next_actions)

        return []

    def think( self, percept ):

        if DEBUG:
          print "-------"
          self.affiche_grille()

        # attention l'odre des actions à une importance

        # action pour finir la map (remplie uniquement si on a gagné) # @todo pas au point
        #if self.win_action:
        #  return self.action_smart(self.win_action.pop(0))

        if self.or_attrape and self.wumpus_est_mort:
          if self.index_case(self.position_joueur[0], self.position_joueur[1]) == (self.gridSize + 1):
            return 'climb'

        if self.force_action:
          return self.force_action.pop(0)

        # on a tué le wumpus ?
        if percept.scream:
            self.wumpus_est_mort = True

        # CSP: si aucun danger, case pas dangereuse
        if not self.perception_danger(percept):
          self.ajout_case_voisines_sans_danger()

        # MODE : force un puit
        if self.force_puit_mode:
          taille_pile = len(self.force_action)

          if not self.action_t_mode_mur:
            force_forward = [4,8]
          else:
            force_forward = [4]

          if (not percept.breeze and taille_pile in force_forward) or taille_pile == 0:
            if taille_pile != 0: # cote
              self.force_action = ['forward', 'forward', 'forward']
            else: # milieu
              self.force_action = ['forward']

            self.force_puit_mode = False
            
        # CSP/UCS: perception d'un puit
        if percept.breeze:
            if self.stench_mode:
              self.stench_mode = False

            # si il n'y a pas de modification sur les hypotheses, on fait un
            # mode_force_puit
            ajoute = self.ajout_hypothese_puit()

            #if not ajoute: #@todo pas fonctionnel
            #  self.force_puit_mode = True
            #  self.action = []
            #  self.action = self.T_actions()
            #else:
            #  # recalcul de l'UCS avec nouveaux scores
            #  self.action = self.ucs()
            self.action = self.ucs()
            
        # MODE: recherche du whumps
        if self.stench_mode:

          taille_pile = len(self.action)

          if not self.action_t_mode_mur:
            shoot_liste = [0,4,8]
          else:
            shoot_liste = [0,4]

          if percept.stench and taille_pile in shoot_liste:
            self.action = ['shoot']
            self.stench_mode = False
            self.action_t_mode_mur = False

          if self.action:
            return self.action_smart(self.action.pop(0))

        # MODE: perception d'un whumps ?
        if percept.stench and not self.stench_mode and not self.wumpus_est_mort:
            # mode recherche du whumps
            self.stench_mode = True

            # enleve toutes nos actions actuelles
            self.action = []

            # action du T
            self.ajout_T_actions()

        # MODE: perception du gold ?
        if percept.glitter and not self.or_attrape:
            # plus besoin des actions courrantes
            self.action = ['grab']
            
            self.or_attrape = True


        # action suite à une perception ?
        if self.action:
            return self.action_smart(self.action.pop(0))

        # UCS général
        self.action = self.ucs()

        return self.action_smart(self.action.pop(0))
