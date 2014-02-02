#include "filters.h"
#include <math.h>

/*
 * Note that the index into the previously recorded values starts at the
 * high bound of the previous value cache.
 */
void butterworth_2pole_init(butterworth_2pole_t *it,
                            float *feedback_params,
                            float *feedforward_params)
{
  unsigned char i;
  for (i = 0; i < 3; i++) {
    if (i < 2) {
      it->feedback_scale_params[i] = feedback_params[i];
    }
    it->feedforward_scale_params[i] = feedforward_params[i];
    it->delayed_inputs[i] = 0.0f;
  }
  it->di_idx = 2;
}

/*
 * Note that indexing into the previous value cache is done such that
 * prior values are conceptually "ahead" of current values.
 * This is done because hardware will preserve the sign during modulo
 * arithmetic, so, for example, attempting to access array[(i - 2) % 3]
 * would expand to array[-2] if i = 0, as opposed to the expected array[1].
 * Always looking ahead to look back mitigates this issue.
 *
 * Additionally, note that the feedback_scale_params and delayed_inputs
 * are dereferenced via stack variables. This may improve performance as
 * less memory delays are incurred accessing those arrays.
 */
int butterworth_2pole_put(butterworth_2pole_t *it, int input)
{
  unsigned char i = it->di_idx;
  float *fbsp = it->feedback_scale_params, *di = it->delayed_inputs;
  di[i] = input - (fbsp[0] * di[(i + 1) % 3] + fbsp[1] * di[(i + 2) % 3]);
  it->di_idx = i ? i - 1 : 2;
  return input;
}

/*
 * Note that the feedforward_scale_params and delayed_inputs
 * are dereferenced via stack variables. This may improve performance as
 * less memory delays are incurred accessing those arrays.
 */
float butterworth_2pole_get_float(butterworth_2pole_t *it)
{
  unsigned char i = it->di_idx, k = 0;
  float sum = 0.0;
  float *ffsp = it->feedforward_scale_params, *di = it->delayed_inputs;
  for (; k < 3; k++) {
    sum += ffsp[k] * di[(i + k) % 3];
  }
  return sum;
}

long int butterworth_2pole_get_long(butterworth_2pole_t *it)
{
  return lround(butterworth_2pole_get_float(it));
}

/*
 * Unlike the Butterworth filter, we can safely store values in a natural order
 * Hence, it->v_idx = 0.
 */
void sliding_window_50_init(sliding_window_50_t *it)
{
  unsigned char i = 0, *values = it->values;
  for (; i < 50; i++) {
    values[i] = 0;
  }
  it->v_idx = 0;
}

int sliding_window_50_put(sliding_window_50_t *it, int input)
{
  unsigned char i = it->v_idx;
  it->values[i] = input;
  it->v_idx = (i + 1) % 50;
  return input;
}

/*
 * Note that we do not care about where the input index is when getting the
 * current output.
 * We do not have to, the average of the last 50 values in a 50-element
 * array will be algebraically equal no matter from where you start the
 * summation.
 */
float sliding_window_50_get_float(sliding_window_50_t *it)
{
  unsigned int sum = 0;
  unsigned char *values = it->values;
  unsigned char i = 0;
  for (; i < 50; i++) {
    sum += values[i];
  }
  return sum / 50.0;
}

int sliding_window_50_get_int(sliding_window_50_t *it)
{
  return lround(sliding_window_50_get_float(it));
}
