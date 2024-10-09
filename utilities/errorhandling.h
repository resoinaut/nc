#pragma once

// return 1 if x fails assuming x returns nonzero on failure
#define TRY(x) if (x) return 1
