#ifndef FIRMWARE_VERSION_H
#define FIRMWARE_VERSION_H

/* 由构建系统注入，未通过 CMake 构建时使用开发版本。 */
#ifndef BUILD_VERSION
#define BUILD_VERSION "dev"
#endif
#ifndef BUILD_HASH
#define BUILD_HASH "unknown"
#endif

#endif
