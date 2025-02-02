// Axel '0vercl0k' Souchet - April 27 2020
#pragma once
#include "platform.h"

#include <cstdint>

using NTSTATUS = int32_t;

#ifdef LINUX
using HANDLE = void *;
#endif

//
// Thanks processhacker/phnt <3
//

//
// Some global NT stuff that several files need to know about.
//

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#define STATUS_SUCCESS 0
#define STATUS_END_OF_FILE 0xc0000011
#define STATUS_OBJECT_NAME_NOT_FOUND 0xc0000034
#ifndef STATUS_INVALID_PARAMETER
#define STATUS_INVALID_PARAMETER 0xC000000D
#endif

#ifndef STD_INPUT_HANDLE
#define STD_INPUT_HANDLE (uint32_t) - 10
#endif

#ifndef STD_OUTPUT_HANDLE
#define STD_OUTPUT_HANDLE (uint32_t) - 11
#endif

#ifndef STD_ERROR_HANDLE
#define STD_ERROR_HANDLE (uint32_t) - 12
#endif

#ifndef FILE_DEVICE_DISK
#define FILE_DEVICE_DISK 0x7
#endif

#ifndef FILE_ATTRIBUTE_NORMAL
#define FILE_ATTRIBUTE_NORMAL 0x80
#endif

#ifndef FILE_APPEND_DATA
#define FILE_APPEND_DATA 4
#endif

#ifndef FILE_SHARE_READ
#define FILE_SHARE_READ 1
#endif

#ifndef FILE_SHARE_WRITE
#define FILE_SHARE_WRITE 2
#endif

#ifndef FILE_SHARE_DELETE
#define FILE_SHARE_DELETE 4
#endif

#ifndef REG_CREATED_NEW_KEY
#define REG_CREATED_NEW_KEY 1
#endif

#ifndef REG_NONE
#define REG_NONE 0
#endif

#ifndef ERROR_SUCCESS
#define ERROR_SUCCESS 0
#endif

struct IO_STATUS_BLOCK {
  union {
    uint32_t Status;
    void *Pointer;
  };
  uintptr_t Information;
};

static_assert(sizeof(IO_STATUS_BLOCK) == 0x10);

struct UNICODE_STRING {
  uint16_t Length;
  uint16_t MaximumLength;
  char16_t *Buffer;
};

using PUNICODE_STRING = UNICODE_STRING *;

static_assert(sizeof(UNICODE_STRING) == 0x10);

struct OBJECT_ATTRIBUTES {
  uint32_t Length;
  HANDLE RootDirectory;
  UNICODE_STRING *ObjectName;
  uint32_t Attributes;
  uint8_t *SecurityDescriptor;
  uint8_t *SecurityQualityOfService;
};

static_assert(sizeof(OBJECT_ATTRIBUTES) == 0x30);

enum class FILE_INFORMATION_CLASS {
  FileStandardInformation = 5,      // FILE_STANDARD_INFORMATION
  FileDispositionInformation = 13,  // FILE_DISPOSITION_INFORMATION
  FilePositionInformation = 14,     // FILE_POSITION_INFORMATION
  FileAllocationInformation = 19,   // FILE_ALLOCATION_INFORMATION
  FileEndOfFileInformation = 20,    // FILE_END_OF_FILE_INFORMATION
  FileAttributeTagInformation = 35, // FILE_ATTRIBUTE_TAG_INFORMATION
};

enum class FS_INFORMATION_CLASS {
  FileFsDeviceInformation = 4, // FILE_FS_DEVICE_INFORMATION
};

// Create disposition

#define FILE_SUPERSEDE 0x00000000
#define FILE_OPEN 0x00000001
#define FILE_CREATE 0x00000002
#define FILE_OPEN_IF 0x00000003
#define FILE_OVERWRITE 0x00000004
#define FILE_OVERWRITE_IF 0x00000005

// Create/open flags

#define FILE_DIRECTORY_FILE 0x00000001
#define FILE_WRITE_THROUGH 0x00000002
#define FILE_SEQUENTIAL_ONLY 0x00000004
#define FILE_NO_INTERMEDIATE_BUFFERING 0x00000008
#define FILE_SYNCHRONOUS_IO_ALERT 0x00000010
#define FILE_SYNCHRONOUS_IO_NONALERT 0x00000020
#define FILE_NON_DIRECTORY_FILE 0x00000040
#define FILE_CREATE_TREE_CONNECTION 0x00000080
#define FILE_COMPLETE_IF_OPLOCKED 0x00000100
#define FILE_NO_EA_KNOWLEDGE 0x00000200
#define FILE_OPEN_FOR_RECOVERY 0x00000400
#define FILE_RANDOM_ACCESS 0x00000800
#define FILE_DELETE_ON_CLOSE 0x00001000
#define FILE_OPEN_BY_FILE_ID 0x00002000
#define FILE_OPEN_FOR_BACKUP_INTENT 0x00004000
#define FILE_NO_COMPRESSION 0x00008000
#define FILE_OPEN_REQUIRING_OPLOCK 0x00010000
#define FILE_DISALLOW_EXCLUSIVE 0x00020000
#define FILE_SESSION_AWARE 0x00040000
#define FILE_RESERVE_OPFILTER 0x00100000
#define FILE_OPEN_REPARSE_POINT 0x00200000
#define FILE_OPEN_NO_RECALL 0x00400000
#define FILE_OPEN_FOR_FREE_SPACE_QUERY 0x00800000

// I/O status information values for NtCreateFile/NtOpenFile

#define FILE_SUPERSEDED 0x00000000
#define FILE_OPENED 0x00000001
#define FILE_CREATED 0x00000002
#define FILE_OVERWRITTEN 0x00000003
#define FILE_EXISTS 0x00000004
#define FILE_DOES_NOT_EXIST 0x00000005

struct FILE_BASIC_INFORMATION {
  uint64_t CreationTime;
  uint64_t LastAccessTime;
  uint64_t LastWriteTime;
  uint64_t ChangeTime;
  uint32_t FileAttributes;
};

static_assert(sizeof(FILE_BASIC_INFORMATION) == 0x28);

struct FILE_DISPOSITION_INFORMATION {
  uint8_t DeleteFile;
};

static_assert(sizeof(FILE_DISPOSITION_INFORMATION) == 1);

struct FILE_POSITION_INFORMATION {
  uint64_t CurrentByteOffset;
};

static_assert(sizeof(FILE_POSITION_INFORMATION) == 8);

struct FILE_FS_DEVICE_INFORMATION {
  uint32_t DeviceType;
  int32_t MaximumComponentNameLength;
};

static_assert(sizeof(FILE_FS_DEVICE_INFORMATION) == 8);

struct FILE_ATTRIBUTE_TAG_INFORMATION {
  uint32_t FileAttributes;
  uint32_t ReparseTag;
};

static_assert(sizeof(FILE_ATTRIBUTE_TAG_INFORMATION) == 8);

struct FILE_STANDARD_INFORMATION {
  uint64_t AllocationSize;
  uint64_t EndOfFile;
  uint32_t NumberOfLinks;
  uint8_t DeletePending;
  uint8_t Directory;
};

static_assert(sizeof(FILE_STANDARD_INFORMATION) == 0x18);

struct FILE_END_OF_FILE_INFORMATION {
  uint64_t EndOfFile;
};

static_assert(sizeof(FILE_END_OF_FILE_INFORMATION) == 8);

struct FILE_ALLOCATION_INFORMATION {
  uint64_t AllocationSize;
};

static_assert(sizeof(FILE_ALLOCATION_INFORMATION) == 8);

#ifndef EXCEPTION_MAXIMUM_PARAMETERS
#define EXCEPTION_MAXIMUM_PARAMETERS 15
#endif

namespace wtf {
struct EXCEPTION_RECORD {
  uint32_t ExceptionCode;
  uint32_t ExceptionFlags;
  struct EXCEPTION_RECORD *ExceptionRecord;
  uint64_t ExceptionAddress;
  uint32_t NumberParameters;
  uint64_t ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
};

static_assert(sizeof(EXCEPTION_RECORD) == 0x98);
} // namespace wtf

#ifndef DBG_PRINTEXCEPTION_C
#define DBG_PRINTEXCEPTION_C 0x40010006
#endif

#ifndef DBG_PRINTEXCEPTION_WIDE_C
#define DBG_PRINTEXCEPTION_WIDE_C 0x4001000A
#endif

#ifndef STATUS_STACK_BUFFER_OVERRUN
#define STATUS_STACK_BUFFER_OVERRUN 0xC0000409
#endif

#ifndef EXCEPTION_ACCESS_VIOLATION
#define EXCEPTION_ACCESS_VIOLATION 0xC0000005
#endif

#define EXCEPTION_ACCESS_VIOLATION_READ 0xCFFFFFFF
#define EXCEPTION_ACCESS_VIOLATION_WRITE 0xCFFFFFFE
#define EXCEPTION_ACCESS_VIOLATION_EXECUTE 0xCFFFFFFD

#ifndef EXCEPTION_ARRAY_BOUNDS_EXCEEDED
#define EXCEPTION_ARRAY_BOUNDS_EXCEEDED 0xC000008
#endif

#ifndef EXCEPTION_BREAKPOINT
#define EXCEPTION_BREAKPOINT 0x80000003
#endif

#ifndef EXCEPTION_DATATYPE_MISALIGNMENT
#define EXCEPTION_DATATYPE_MISALIGNMENT 0x80000002
#endif

#ifndef EXCEPTION_FLT_DENORMAL_OPERAND
#define EXCEPTION_FLT_DENORMAL_OPERAND 0xC000008D
#endif

#ifndef EXCEPTION_FLT_DIVIDE_BY_ZERO
#define EXCEPTION_FLT_DIVIDE_BY_ZERO 0xC000008E
#endif

#ifndef EXCEPTION_FLT_INEXACT_RESULT
#define EXCEPTION_FLT_INEXACT_RESULT 0xC000008F
#endif

#ifndef EXCEPTION_FLT_INVALID_OPERATION
#define EXCEPTION_FLT_INVALID_OPERATION 0xC0000090
#endif

#ifndef EXCEPTION_FLT_OVERFLOW
#define EXCEPTION_FLT_OVERFLOW 0xC0000091
#endif

#ifndef EXCEPTION_FLT_STACK_CHECK
#define EXCEPTION_FLT_STACK_CHECK 0xC0000092
#endif

#ifndef EXCEPTION_FLT_UNDERFLOW
#define EXCEPTION_FLT_UNDERFLOW 0xC0000093
#endif

#ifndef EXCEPTION_ILLEGAL_INSTRUCTION
#define EXCEPTION_ILLEGAL_INSTRUCTION 0xC000001D
#endif

#ifndef EXCEPTION_IN_PAGE_ERROR
#define EXCEPTION_IN_PAGE_ERROR 0xC0000006
#endif

#ifndef EXCEPTION_INT_DIVIDE_BY_ZERO
#define EXCEPTION_INT_DIVIDE_BY_ZERO 0xC0000094
#endif

#ifndef EXCEPTION_INT_OVERFLOW
#define EXCEPTION_INT_OVERFLOW 0xC0000095
#endif

#ifndef EXCEPTION_INVALID_DISPOSITION
#define EXCEPTION_INVALID_DISPOSITION 0xC0000026
#endif

#ifndef EXCEPTION_NONCONTINUABLE_EXCEPTION
#define EXCEPTION_NONCONTINUABLE_EXCEPTION 0xC0000025
#endif

#ifndef EXCEPTION_PRIV_INSTRUCTION
#define EXCEPTION_PRIV_INSTRUCTION 0xC0000096
#endif

#ifndef EXCEPTION_SINGLE_STEP
#define EXCEPTION_SINGLE_STEP 0x80000004
#endif

#ifndef EXCEPTION_STACK_OVERFLOW
#define EXCEPTION_STACK_OVERFLOW 0xC00000FD
#endif

#ifndef STATUS_STACK_BUFFER_OVERRUN
#define STATUS_STACK_BUFFER_OVERRUN 0xC0000409
#endif
