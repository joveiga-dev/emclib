#ifndef EMC_LIST_H
#define EMC_LIST_H

#include <stdint.h>


/* @brief double linked list circular list. */
 struct emc_list_s {
    struct emc_list_s *next;
    struct emc_list_s *prev;
 };

 /*
  * @brief initialize the list.
  * @param list the list to be initialized.
  */
 void emc_list_init(struct emc_list_s *list);

 /*
  * @brief add item to the head of the list.
  * @param list the list to add item to.
  * @param item the item to be added.
  */
 void emc_list_add_head(struct emc_list_s *list, struct emc_list_s *item);

 /*
  * @brief add item to the tail of the list.
  * @param list the list to add item to.
  * @param item the item to be added.
  */
 void emc_list_add_tail(struct emc_list_s *list, struct emc_list_s *item);

 /*
  * @brief delete the list.
  * @param item the list to be deleted.
  */
 void emc_list_delete(struct emc_list_s *item);

 /*
  * @brief check if the list is empty.
  * @param list the list to be checked.
  * @return true if the list is empty, false otherwise.
  */
 bool emc_list_empty(struct emc_list_s *list);
 
 void emc_list_insert_after(struct emc_list_s *node, struct emc_list_s *new_node);
 void emc_list_insert_before(struct emc_list_s *node, struct emc_list_s *new_node);
 void emc_list_remove_head(struct emc_list_s *list);
 void emc_list_remove_tail(struct emc_list_s *list);


#endif // EMC_LIST_H