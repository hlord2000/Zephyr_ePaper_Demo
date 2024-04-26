/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <lvgl_input_device.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);

int main(void)
{
	const struct device *display_dev;

	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		LOG_ERR("Device not ready, aborting test");
		return 0;
	}

	lv_obj_t *qr_code = lv_qrcode_create(lv_scr_act(), 100, lv_color_hex(0x000000), lv_color_hex(0xffffff));
	lv_qrcode_update(qr_code, "https://www.nordicsemi.com/", strlen("https://www.nordicsemi.com/"));
	lv_task_handler();

	while (1) {
		lv_task_handler();
		k_sleep(K_MSEC(10000));
		lv_qrcode_update(qr_code, "https://novelbits.io/", strlen("https://novelbits.io/"));

		lv_task_handler();
		k_sleep(K_MSEC(10000));
		lv_qrcode_update(qr_code, "https://www.nordicsemi.com/", strlen("https://www.nordicsemi.com/"));
	}
}
