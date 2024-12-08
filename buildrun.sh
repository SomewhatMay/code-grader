#!/bin/bash

cd ninja && cmake -G Ninja .. && ninja && cd .. && echo "" && ./ninja/code-grader