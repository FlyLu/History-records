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

/*============================ INCLUDES ======================================*/
#include ".\history.h"
#include <string.h>

/*============================ MACROS ========================================*/
#define ITEM_SIZE               sizeof(history_item_t)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
typedef struct  {
    uint16_t SaveIndex; 
    uint16_t SaveCount;   
    uint16_t ReadIndex;
    uint16_t ReadCount;
} history_manage_t;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
static history_item_t s_tHistoryItem[HISTORY_ITEM_MAX_COUNT];

static history_manage_t s_tHistoryManage;

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
void init_history(void)
{
    memset(&s_tHistoryManage,  0, sizeof(history_manage_t));    
}


bool save_history_item(history_item_t *ptItem)
{
    if (NULL == ptItem) {
        return false;
    }

    if (HISTORY_ITEM_MAX_COUNT <= s_tHistoryManage.SaveIndex) {
        s_tHistoryManage.SaveIndex = 0;
    }

    s_tHistoryManage.ReadIndex = s_tHistoryManage.SaveIndex;

    if (HISTORY_ITEM_MAX_COUNT > s_tHistoryManage.SaveCount) {
        s_tHistoryManage.SaveCount++;
    }

    s_tHistoryManage.ReadCount = s_tHistoryManage.SaveCount;

    memcpy(&s_tHistoryItem[s_tHistoryManage.SaveIndex++], ptItem, ITEM_SIZE);
    
    return true;
}


bool read_prev_history_item(history_item_t *ptItem)
{
    if (NULL == ptItem) {
        return false;
    }

    if (s_tHistoryManage.ReadCount == 0) {
        return false;
    }

    if (s_tHistoryManage.ReadCount != s_tHistoryManage.SaveCount) {
        if (0 == s_tHistoryManage.ReadIndex) {
            s_tHistoryManage.ReadIndex = HISTORY_ITEM_MAX_COUNT;
        }
        s_tHistoryManage.ReadIndex--;
    }

    s_tHistoryManage.ReadCount--;

    memcpy(ptItem, &s_tHistoryItem[s_tHistoryManage.ReadIndex], ITEM_SIZE);

    return true;
}


bool read_next_history_item(history_item_t *ptItem)
{
    if (NULL == ptItem) {
        return false;
    }

    if (s_tHistoryManage.SaveCount <= (s_tHistoryManage.ReadCount + 1)) {
        return false;
    }

    if (HISTORY_ITEM_MAX_COUNT == ++s_tHistoryManage.ReadIndex) {
        s_tHistoryManage.ReadIndex = 0;
    }

    s_tHistoryManage.ReadCount++;

    memcpy(ptItem, &s_tHistoryItem[s_tHistoryManage.ReadIndex], ITEM_SIZE);
    
    return true;
}


uint16_t get_history_item_count(void)
{
    return s_tHistoryManage.SaveCount;
}


history_item_t *get_oldest_history_item(void)
{
    history_item_t *ptItem;

    if (0 == s_tHistoryManage.SaveCount) {
        return NULL;
    }

    if (HISTORY_ITEM_MAX_COUNT == s_tHistoryManage.SaveCount) {
        if (HISTORY_ITEM_MAX_COUNT == s_tHistoryManage.SaveIndex) {
            ptItem = &s_tHistoryItem[0];
        } else {
            ptItem = &s_tHistoryItem[s_tHistoryManage.SaveIndex];
        }
    } else {
        ptItem = &s_tHistoryItem[0];
    }

    return ptItem;
}


history_item_t *get_newest_history_item(void)
{
    if (0 == s_tHistoryManage.SaveCount) {
        return NULL;
    }

    return (&s_tHistoryItem[s_tHistoryManage.SaveIndex - 1]);
}


void reset_history_item(void)
{
    s_tHistoryManage.ReadCount = s_tHistoryManage.SaveCount;
    s_tHistoryManage.ReadIndex = s_tHistoryManage.SaveIndex;
}
/* EOF */
