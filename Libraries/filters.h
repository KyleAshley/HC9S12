typedef struct butterworth_2pole {
  float feedback_scale_params[2];
  float feedforward_scale_params[3];
  float delayed_inputs[3];
  unsigned char di_idx;
} butterworth_2pole_t;

/*
 * Initializes a Butterworth 2 pole filter
 * Parameters:
 * butterworth_2pole_t *it   - Pointer to the filter state being initialized
 * float *feedback_params    - A 2-value float array for scaling the feedback
 * float *feedforward_params - A 3-value float array for scaling the feedforward
 */
void butterworth_2pole_init(butterworth_2pole_t *it,
                            float *feedback_params,
                            float *feedforward_params);

/*
 * Queues an integer into a filter state and updates the filter state for
 * further future input.
 * Parameters:
 * butterworth_2pole_t *it - Pointer to the filter state into which input is
 *                           queued
 * int input               - The input to be queued into the filter
 */
int butterworth_2pole_put(butterworth_2pole_t *it, int input);

/*
 * Gets the current output of the filter state as a long integer
 * Parameters:
 * butterworth_2pole_t *it - Pointer to the filter state from which output is
 *                           received
 */
long butterworth_2pole_get_long(butterworth_2pole_t *it);

/*
 * Gets the current output of the filter state as a float
 * Parameters:
 * butterworth_2pole_t *it - Pointer to the filter state from which output is
 *                           received
 */
float butterworth_2pole_get_float(butterworth_2pole_t *it);

typedef struct sliding_window_50 {
  unsigned char values[50];
  unsigned char v_idx;
} sliding_window_50_t;

/*
 * Initializes a 50-value sliding window filter
 * Parameters:
 * sliding_window_50_t *it - Pointer to the filter state being initialized
 */
void sliding_window_50_init(sliding_window_50_t *it);

/*
 * Queues an integer into the filter state, and updates the filter state for
 * future input.
 * Parameters:
 * sliding_window_50_t *it - Pointer to the filter state into which input
 *                           will be queued
 * int input               - The input to be queued into the filter
 */
int sliding_window_50_put(sliding_window_50_t *it, int input);

/*
 * Gets the current output of the filter state as a long integer
 * Parameters:
 * sliding_window_50_t *it - Pointer to the filter state from which output is
 *                           received
 */
long sliding_window_50_get_long(sliding_window_50_t *it);

/*
 * Gets the current output of the filter state as a float
 * Parameters:
 * sliding_window_50_t *it - Pointer to the filter state from which output is
 *                           received
 */
float sliding_window_50_get_float(sliding_window_50_t *it);
