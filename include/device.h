/*
 * vim:ts=4:sw=4:expandtab
 *
 * i3 - an improved dynamic tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * device.c: XInput2 devices.
 *
 */

/*
 * Returns the container which is focused by the given mouse or keyboard 
 * master device or NULL if no such container exists.
 *
 */
Con *con_by_device(Device *device);

/* 
 * Returns the devices with the given container as focus.
 * 
 */
Device **devices_by_con(Con *con);

/*
 * Return the device with the given device ID or NULL if no such device exists.
 * 
 */
Device *device_by_id(xcb_input_device_id_t device_id);

/*
 * Returns the first device that has a focus. For EWMH, which doesn't know about multiple focuses/foci.
 *
 */
Device *device_first_focused(void);

/*
 * Returns the first con that is focused. For EWMH, which doesn't know about multiple focuses/foci.
 *
 */
Con *con_first_focused(void);

/*
 * Returns whether the Con is focused by any device.
 *
 */
bool con_is_focused(Con *con);

/*
 * Unfocuses the given device.
 *
 */
void device_unfocus(Device *device);

/*
 * Sets the focus of the given device to the given container.
 *
 */
void device_set_focus(Device *device, Con *con);
