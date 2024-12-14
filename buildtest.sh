#!/bin/bash

cd ninja && cmake -G Ninja .. -DENABLE_TESTS=ON  && ninja && cd .. && echo "" && ./ninja/code-grader-tests