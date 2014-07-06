/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef HEAD_LTP3445_H_
#define HEAD_LTP3445_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * Initialize all stuff for head management (pins etc.)
 */
extern void headInit (void);

/**
 * Submit 1 line (832 pixels) of data. 1bit color depth.
 * Data must be no shorter than 104 bytes.
 */
extern void headTransferLine1Bit (uint8_t *data);

extern void headCtrl (bool bit);

extern void headLatch (void);

/**
 * HEAD_NUMBER_OF_PAGES (usually 13) least significatn bits are transfered.
 */
extern void headTransferBdat (uint16_t pages);

extern void headHeatPulse (void);

#endif /* HEAD_H_ */