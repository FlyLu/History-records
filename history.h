/***************************************************************************
 *   Copyright(C)2014-2015 by FlyLu <Linch.Embedded@gmail.com>             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef __HISTORY_H__
#define __HISTORY_H__

/*============================ INCLUDES ======================================*/
#include <stdint.h>
#include <stdbool.h>

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
#define HISTORY_ITEM_MAX_COUNT        5

//! brief you can custom this struct, save anything which you want

typedef struct {
    uint8_t Item[20];
} history_item_t;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*! \brief init history structure
 *! \param none
 *! \return none
 */ 
extern void init_history(void);


/*! \brief save history item
 *! \param ptItem history item which you want to save
 *! \return ture  save ok 
 *! \return false save failed
 */ 
extern bool save_history_item(history_item_t *ptItem);


/*! \brief read previous history item
 *! \param ptItem history item
 *! \return ture  read ok 
 *! \return false read failed
 */ 
extern bool read_prev_history_item(history_item_t *ptItem);


/*! \brief read nest history item
 *! \param ptItem history item
 *! \return ture  read ok 
 *! \return false read failed
 */ 
extern bool read_next_history_item(history_item_t *ptItem);


/*! \brief get current history item count
 *! \param none
 *! \return current history item count
 */ 
extern uint16_t get_history_item_count(void);


/*! \brief get oldest history item pointer
 *! \param none
 *! \return null or history item pointer
 */ 
extern history_item_t *get_oldest_history_item(void);


/*! \brief get newest history item pointer
 *! \param none
 *! \return null or history item pointer
 */ 
extern history_item_t *get_newest_history_item(void);


/*! \brief reset history item index
 *! \param none
 *! \return none
 */ 
extern void reset_history_item(void);
/*============================ IMPLEMENTATION ================================*/
#endif 
/* EOF */
