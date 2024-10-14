#include <fcntl.h>
#include <linux/nvme_ioctl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
// Define IOCTL commands
#define DEVICE_PATH "/dev/nvme0n1"
enum {
  FEMU_ENABLE_GC_DELAY = 1,
  FEMU_DISABLE_GC_DELAY = 2,

  FEMU_ENABLE_DELAY_EMU = 3,
  FEMU_DISABLE_DELAY_EMU = 4,

  FEMU_RESET_ACCT = 5,
  FEMU_ENABLE_LOG = 6,
  FEMU_DISABLE_LOG = 7,
  FEMU_RESET_STAT = 8,
  FEMU_PRINT_STAT = 9,
  FEMU_MODEL = 10,
  FEMU_MODEL_UNUSE = 11
};
enum NvmeAdminCommands {
  NVME_ADM_CMD_DELETE_SQ = 0x00,
  NVME_ADM_CMD_CREATE_SQ = 0x01,
  NVME_ADM_CMD_GET_LOG_PAGE = 0x02,
  NVME_ADM_CMD_DELETE_CQ = 0x04,
  NVME_ADM_CMD_CREATE_CQ = 0x05,
  NVME_ADM_CMD_IDENTIFY = 0x06,
  NVME_ADM_CMD_ABORT = 0x08,
  NVME_ADM_CMD_SET_FEATURES = 0x09,
  NVME_ADM_CMD_GET_FEATURES = 0x0a,
  NVME_ADM_CMD_ASYNC_EV_REQ = 0x0c,
  NVME_ADM_CMD_ACTIVATE_FW = 0x10,
  NVME_ADM_CMD_DOWNLOAD_FW = 0x11,
  NVME_ADM_CMD_FORMAT_NVM = 0x80,
  NVME_ADM_CMD_SECURITY_SEND = 0x81,
  NVME_ADM_CMD_SECURITY_RECV = 0x82,
  NVME_ADM_CMD_SET_DB_MEMORY = 0x7c,
  NVME_ADM_CMD_FEMU_DEBUG = 0xee,
  NVME_ADM_CMD_FEMU_FLIP = 0xef,
};
struct nvme_admin_cmd PRINT_STAT = {
    .opcode = NVME_ADM_CMD_FEMU_FLIP,
    .nsid = 1,
    .cdw10 = FEMU_PRINT_STAT,
};

struct nvme_admin_cmd RESET_STAT = {
    .opcode = NVME_ADM_CMD_FEMU_FLIP,
    .nsid = 1,
    .cdw10 = FEMU_RESET_STAT,
};

int main() {
  int fd;
  fd = open(DEVICE_PATH, O_RDWR);
  if (fd < 0) {
    perror("open");
    return 1;
  }
  int ret = ioctl(fd, NVME_IOCTL_ADMIN_CMD, &PRINT_STAT);
  if (ret < 0) {
    perror("ioctl");
  }
  close(fd);
  return ret;
}
