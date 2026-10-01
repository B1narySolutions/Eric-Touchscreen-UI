#include "lvgl_fs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esp_log.h"
#include "esp_spiffs.h"
#include "lvgl.h"

#define AMP_FS_ROOT "/spiffs"

static const char * TAG = "amp_fs";

static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode)
{
    LV_UNUSED(drv);
    char full_path[320];
    const char * fopen_mode = (mode & LV_FS_MODE_WR) ? "wb" : "rb";

    if(lv_snprintf(full_path, sizeof(full_path), "%s/%s", AMP_FS_ROOT, path) >= (int)sizeof(full_path)) {
        return NULL;
    }
    return fopen(full_path, fopen_mode);
}

static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p)
{
    LV_UNUSED(drv);
    return fclose((FILE *)file_p) == 0 ? LV_FS_RES_OK : LV_FS_RES_FS_ERR;
}

static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t bytes_to_read,
                           uint32_t * bytes_read)
{
    LV_UNUSED(drv);
    *bytes_read = (uint32_t)fread(buf, 1, bytes_to_read, (FILE *)file_p);
    return ferror((FILE *)file_p) ? LV_FS_RES_FS_ERR : LV_FS_RES_OK;
}

static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence)
{
    LV_UNUSED(drv);
    int origin = SEEK_SET;
    if(whence == LV_FS_SEEK_CUR) origin = SEEK_CUR;
    else if(whence == LV_FS_SEEK_END) origin = SEEK_END;
    return fseek((FILE *)file_p, (long)pos, origin) == 0 ? LV_FS_RES_OK : LV_FS_RES_FS_ERR;
}

static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p)
{
    LV_UNUSED(drv);
    long pos = ftell((FILE *)file_p);
    if(pos < 0) return LV_FS_RES_FS_ERR;
    *pos_p = (uint32_t)pos;
    return LV_FS_RES_OK;
}

esp_err_t amp_lvgl_fs_init(void)
{
    const esp_vfs_spiffs_conf_t config = {
        .base_path = AMP_FS_ROOT,
        .partition_label = "storage",
        .max_files = 4,
        .format_if_mount_failed = false,
    };
    esp_err_t result = esp_vfs_spiffs_register(&config);
    if(result != ESP_OK) {
        ESP_LOGE(TAG, "SPIFFS mount failed: %s", esp_err_to_name(result));
        return result;
    }

    static lv_fs_drv_t driver;
    lv_fs_drv_init(&driver);
    driver.letter = 'S';
    driver.open_cb = fs_open;
    driver.close_cb = fs_close;
    driver.read_cb = fs_read;
    driver.seek_cb = fs_seek;
    driver.tell_cb = fs_tell;
    lv_fs_drv_register(&driver);

    size_t total = 0;
    size_t used = 0;
    ESP_ERROR_CHECK(esp_spiffs_info("storage", &total, &used));
    ESP_LOGI(TAG, "SPIFFS mounted: %u/%u bytes used", (unsigned)used, (unsigned)total);
    return ESP_OK;
}
