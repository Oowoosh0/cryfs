#include "CryFile.h"

#include "CryDevice.h"
#include "CryOpenFile.h"
#include "messmer/fspp/fuse/FuseErrnoException.h"

namespace bf = boost::filesystem;

//TODO Get rid of this in favor of exception hierarchy
using fspp::fuse::CHECK_RETVAL;
using fspp::fuse::FuseErrnoException;

using blockstore::Key;
using boost::none;
using cpputils::unique_ref;
using cpputils::make_unique_ref;
using cpputils::dynamic_pointer_move;
using cryfs::fsblobstore::DirBlob;
using cryfs::fsblobstore::FileBlob;

namespace cryfs {

CryFile::CryFile(CryDevice *device, unique_ref<DirBlob> parent, const Key &key)
: CryNode(device, std::move(parent), key) {
}

CryFile::~CryFile() {
}

unique_ref<fsblobstore::FileBlob> CryFile::LoadBlob() const {
  auto blob = CryNode::LoadBlob();
  auto file_blob = dynamic_pointer_move<FileBlob>(blob);
  ASSERT(file_blob != none, "Blob does not store a file");
  return std::move(*file_blob);
}

unique_ref<fspp::OpenFile> CryFile::open(int flags) const {
  auto blob = LoadBlob();
  return make_unique_ref<CryOpenFile>(std::move(blob));
}

void CryFile::truncate(off_t size) const {
  auto blob = LoadBlob();
  blob->resize(size);
}

fspp::Dir::EntryType CryFile::getType() const {
  return fspp::Dir::EntryType::FILE;
}

}
