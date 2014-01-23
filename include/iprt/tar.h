 * Copyright (C) 2009-2014 Oracle Corporation
 *
 * @deprecated  Only used for legacy code and writing.  Migrate new code to the
 *              VFS interface, add the write part when needed.
 *
 * Close the Tar archive.
 * @returns IPRT status code.
 *
 * @param   hTar           Handle to the RTTAR interface.
 */
RTR3DECL(int) RTTarClose(RTTAR hTar);

/**
 * Jumps to the next file from the current RTTar position.
 * @param   hTar           Handle to the RTTAR interface.
RTR3DECL(int) RTTarSeekNextFile(RTTAR hTar);
 * Return the filename where RTTar currently stays at.
 * @param   ppszFilename   On success the filename.
RTR3DECL(int) RTTarCurrentFile(RTTAR hTar, char **ppszFilename);

/**
 * Opens the file where RTTar currently stays at.
 *
 * The current file can only be opened once.  The next call will open the next
 * file, implicitly calling RTTarSeekNextFile().
 *
 * @returns IPRT status code.
 *
 * @param   hTar           Handle to the RTTAR interface.
 * @param   phFile         Where to store the handle to the opened file.
 * @param   ppszFilename   On success the filename.
 * @param   fOpen          Open flags, i.e a combination of the RTFILE_O_* defines.
 *                         The ACCESS, ACTION flags are mandatory! Currently
 *                         only RTFILE_O_OPEN | RTFILE_O_READ is supported.
 */
RTR3DECL(int) RTTarFileOpenCurrentFile(RTTAR hTar, PRTTARFILE phFile, char **ppszFilename, uint32_t fOpen);
 * @param   pcbRead        Where to return how much we actually read.  If NULL
 *                         an error will be returned for a partial read.
 * @param   pcbWritten     Where to return how much we actually wrote.  If NULL
 *                         an error will be returned for a partial write.
#endif