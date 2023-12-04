/***********************************************************************************************************************
 * File Name    : syscalls.c
 * Description  : Override for missing system functions required for GCC.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/


#include "hal_data.h"
#include <errno.h>
#include <sys\stat.h>

int _open(const char *path, int file);
int _close(int file);
int _getpid(void);
int _kill(int pid, int sig);
int _lseek(int file, int ptr, int dir);
int _read(int file, char *ptr, int len);
int _write(int file, char *ptr, int len);
int _fstat(int file, struct stat *pstat);
int _isatty(int file);

int _open(const char *path, int file) {
    FSP_PARAMETER_NOT_USED(path);
    FSP_PARAMETER_NOT_USED(file);
  return -1;
}

int _close(int file) {
    FSP_PARAMETER_NOT_USED(file);
  return -1;
}

int _getpid(void) {
  return 1;
}


#undef errno
extern int errno;
int _kill(int pid, int sig) {
    FSP_PARAMETER_NOT_USED(pid);
    FSP_PARAMETER_NOT_USED(sig);
  errno = EINVAL;
  return -1;
}

int _lseek(int file, int ptr, int dir) {
    FSP_PARAMETER_NOT_USED(file);
    FSP_PARAMETER_NOT_USED(ptr);
    FSP_PARAMETER_NOT_USED(dir);
  return 0;
}

int _read(int file, char *ptr, int len) {
    FSP_PARAMETER_NOT_USED(file);
    FSP_PARAMETER_NOT_USED(ptr);
    FSP_PARAMETER_NOT_USED(len);
  return 0;
}

int _write(int file, char *ptr, int len) {
  int todo;

  FSP_PARAMETER_NOT_USED(file);
  FSP_PARAMETER_NOT_USED(ptr);

  for (todo = 0; todo < len; todo++) {
    //outbyte (*ptr++);
  }
  return len;
}

int _fstat (int file, struct stat *pstat)
{
    FSP_PARAMETER_NOT_USED(file);
    FSP_PARAMETER_NOT_USED(pstat);
    return 0;
}


int _isatty(int file)
{
    FSP_PARAMETER_NOT_USED(file);
    return 0;
}
