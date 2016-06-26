/*
 * Copyright 2008 Google Inc.
 * Copyright 2015 Tomasz Kociumaka
 * Copyright 2016 IPP team
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef UTILS_H
#define UTILS_H

/* If this is being built for a unit test. */
#ifdef UNIT_TESTING

int middle_ages_main();
/* Function main is defined in the unit test so redefine name of the main function
 * here. */
#define main middle_ages_main

/* All functions in this object need to be exposed to the test application,
 * so redefine static to nothing. */
#define static

#endif /* UNIT_TESTING */

#endif /* UTILS_H*/
