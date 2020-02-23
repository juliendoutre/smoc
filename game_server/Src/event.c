#include <event.h>

void event_init(event *e)
{
  *e = 0;
}

void event_trigger(event *e)
{
  *e = 1;
}

int event_check(event *e)
{
  if (*e)
  {
    *e = 0;
    return 1;
  }

  return 0;
}

int event_read(event *e)
{
  return *e;
}
