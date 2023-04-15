/*
 * vim:ts=4:sw=4:expandtab
 *
 * i3 - an improved dynamic tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * device.c: XInput2 devices.
 *
 */
#include "all.h"

/*
 * Returns the container which is focused by the given mouse or keyboard 
 * master device or NULL if no such container exists.
 *
 */
Con *con_by_device(Device *device) {
    return device->focus;
}

/*
 * Returns the devices with the given container as focus.
 *
 */
Device **devices_by_con(Con *con) {
    int n = 0;
    Device *d;
    TAILQ_FOREACH (d, &all_devices, devices) {
        if (d->focus == con) {
            n++;
        }
    }
    Device **ds = smalloc(n * sizeof(Device *));
    n = 0;
    TAILQ_FOREACH (d, &all_devices, devices) {
        if (d->focus == con) {
            ds[n++] = d;
        }
    }
    return ds;
}

Device *device_by_id(xcb_input_device_id_t id) {
    Device *d;
    TAILQ_FOREACH (d, &all_devices, devices) {
        if (d->id == id) {
            return d;
        }
    }
    return NULL;
}

/*
 * Returns the first device that has a focus. For EWMH, which doesn't know about multiple focuses/foci.
 *
 */
Device *device_first_focused(void) {
    Device *d;
    TAILQ_FOREACH (d, &all_devices, devices) {
        if (d->focus != NULL) {
            return d;
        }
    }
    return NULL;
}

/*
 * Returns the first con that is focused. For EWMH, which doesn't know about multiple focuses/foci.
 *
 */
Con *con_first_focused(void) {
    Device *d;
    if ((d = device_first_focused())) {
        return d->focus;
    }
    return NULL;
}

/*
 * Returns whether the Con is focused by any device.
 *
 */
bool con_is_focused(Con *con) {
    return con->nfocused > 0;
}

/*
 * Unfocuses the given device.
 *
 */
void device_unfocus(Device *device) {
    if (device->focus == NULL) {
        return;
    }
    device->focus->nfocused--;
    device->focus = NULL;
}

/*
 * Sets the focus of the given device to the given container.
 *
 */
void device_set_focus(Device *device, Con *con) {
    if (device->focus != NULL) {
        device->focus->nfocused--;
    }
    device->focus = con;
    con->nfocused++;
}
