#pragma once
#ifndef CRYFS_LIB_CRYOPENFILE_H_
#define CRYFS_LIB_CRYOPENFILE_H_

#include "messmer/fspp/fs_interface/OpenFile.h"
#include "fsblobstore/FileBlob.h"

namespace cryfs {
class CryDevice;

class CryOpenFile: public fspp::OpenFile {
public:
  explicit CryOpenFile(cpputils::unique_ref<fsblobstore::FileBlob> fileBlob);
  virtual ~CryOpenFile();

  void stat(struct ::stat *result) const override;
  void truncate(off_t size) const override;
  ssize_t read(void *buf, size_t count, off_t offset) const override;
  void write(const void *buf, size_t count, off_t offset) override;
  void flush() override;
  void fsync() override;
  void fdatasync() override;

private:
  cpputils::unique_ref<fsblobstore::FileBlob> _fileBlob;

  DISALLOW_COPY_AND_ASSIGN(CryOpenFile);
};

}

#endif
