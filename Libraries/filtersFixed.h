
typedef struct butterworth_2poleF {
  long feedback_scale_params[2];
  long feedforward_scale_params[3];
  long delayed_inputs[3];
  unsigned char di_idx;
} butterworth_2pole_ft;

/*
 * Initializes a Butterworth 2 pole filter
 * Parameters:
 * butterworth_2pole_t *it   - Pointer to the filter state being initialized
 * float *feedback_params    - A 2-value float array for scaling the feedback
 * float *feedforward_params - A 3-value float array for scaling the feedforward
 */
void butterworth_2pole_initF(butterworth_2pole_ft *it,
                            long *feedback_params,
                            long *feedforward_params);

/*
 * Queues an integer into a filter state and updates the filter state for
 * further future input.
 * Parameters:
 * butterworth_2pole_t *it - Pointer to the filter state into which input is
 *                           queued
 * int input               - The input to be queued into the filter
 */
unsigned long butterworth_2pole_putF(butterworth_2pole_ft *it, unsigned long);

/*
 * Gets the current output of the filter state as a long integer
 * Parameters:
 * butterworth_2pole_t *it - Pointer to the filter state from which output is
 *                           received
 */
long butterworth_2pole_get_longF(butterworth_2pole_ft *it);