// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)

#if !defined(DATE_YY) || !defined(DATE_MM) || !defined(DATE_DD) || !defined(BUILD_TIME)
#define BUILD_DATETIME "Unknown"
#else
#define BUILD_DATETIME DATE_YY "-" DATE_MM "-" DATE_DD " " BUILD_TIME
#endif

#if !defined(BUILD_VERSION)
#define BUILD_VERSION "Unknown"
#endif

