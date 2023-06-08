// Copyright 2016-2022 David Robillard <d@drobilla.net>
// SPDX-License-Identifier: ISC

#ifndef ZIX_ZIX_H
#define ZIX_ZIX_H

// IWYU pragma: begin_exports

/**
   @defgroup zix Zix C API
   @{
*/

/**
   @defgroup zix_utilities Utilities
   @{
*/

#include "attributes.h"
#include "status.h"
#include "string_view.h"

/**
   @}
   @defgroup zix_allocation Allocation
   @{
*/

#include "allocator.h"
#include "bump_allocator.h"

/**
   @}
   @defgroup zix_algorithms Algorithms
   @{
*/

#include "digest.h"

/**
   @}
   @defgroup zix_data_structures Data Structures
   @{
*/

#include "btree.h"
#include "hash.h"
#include "ring.h"
#include "tree.h"

/**
   @}
   @defgroup zix_threading Threading
   @{
*/

#include "sem.h"
#include "thread.h"

/**
   @}
   @defgroup zix_file_system File System
   @{
*/

#include "filesystem.h"
#include "path.h"

/**
   @}
   @}
*/

// IWYU pragma: end_exports

#endif /* ZIX_ZIX_H */
