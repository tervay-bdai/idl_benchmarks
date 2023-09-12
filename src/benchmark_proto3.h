#pragma once

#include <iostream>

#include "msgs/address_book_3.pb.h"
#include "src/benchmark.h"
#include "src/consts.h"

class Proto3Benchmarkable : public Benchmarkable {
public:
  Proto3Benchmarkable() : Benchmarkable() {}

  void serialize() {
    pb3::AddressBook address_book;

    auto person = address_book.add_people();
    auto phone = person->add_phones();

    phone->set_number(PERSON_PHONE_NUMBER.data(), PERSON_PHONE_NUMBER.size());
    phone->set_type(pb3::Person::PHONE_TYPE_MOBILE);

    person->set_email(PERSON_EMAIL.data(), PERSON_EMAIL.size());
    person->set_name(PERSON_NAME.data(), PERSON_NAME.size());
    person->set_id(PERSON_ID);

    address_book.SerializeAsString();
  }
};
