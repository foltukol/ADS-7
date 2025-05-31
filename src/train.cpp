// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
  if (!first) return;
  Car* current = first->next;
  while (current != first) {
    Car* next = current->next;
    delete current;
    current = next;
  }
  delete first;
  first = nullptr;
}

void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};
  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
    return;
  } 
  Car* last = first->prev;
  last->next = newCar;
  newCar->prev = last;
  newCar->next = first;
  first->prev = newCar;
}

int Train::getLength() {
  if (first == nullptr) {
    return 0;
  }
  Car* current = first;
  int step = 0;
  current->light = true;
  while (true) {
    current = current->next;
    step++;
    countOp++;
    while (!current->light) {
      current = current->next;
      countOp++;
      step++;
    }
    int length = step;
    current->light = false;
    while (step > 0) {
      current = current->prev;
      countOp++;
      step--;
    }
    if (!current->light) {
      return length;
    }
  }
}

int Train::getOpCount() {
    return countOp;
}
