/*
 * Copyright (c) 2006-Present, Redis Ltd.
 * All rights reserved.
 *
 * Licensed under your choice of the Redis Source Available License 2.0
 * (RSALv2); or (b) the Server Side Public License v1 (SSPLv1); or (c) the
 * GNU Affero General Public License v3 (AGPLv3).
*/
#pragma once

#include <stddef.h>
#include "redisearch.h"
#include "index_iterator.h"
#include "geometry_types.h"

#ifdef __cplusplus
extern "C" {
#endif

GeometryIndex *GeometryIndexFactory(GEOMETRY_COORDS tag);
const GeometryApi *GeometryApi_Get(const GeometryIndex *index);
const char *GeometryCoordsToName(GEOMETRY_COORDS tag);

struct GeometryApi {
  void (*freeIndex)(GeometryIndex *index);
  int (*addGeomStr)(GeometryIndex *index, GEOMETRY_FORMAT format, const char *str, size_t len,
                    t_docId docId, RedisModuleString **err_msg);
  int (*delGeom)(GeometryIndex *index, t_docId docId);
  IndexIterator *(*query)(const RedisSearchCtx *sctx, const FieldFilterContext*,
                          const GeometryIndex *index, QueryType queryType, GEOMETRY_FORMAT format,
                          const char *str, size_t len, RedisModuleString **err_msg);
  void (*dump)(const GeometryIndex *index, RedisModuleCtx *ctx);
  size_t (*report)(const GeometryIndex *index);
};

#ifdef __cplusplus
}
#endif
