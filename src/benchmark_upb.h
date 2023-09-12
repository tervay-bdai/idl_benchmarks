#pragma once

#include <iostream>

#include "msgs/address_book_upb.upb.h"
#include "src/benchmark.h"
#include "src/consts.h"

#include "upb/reflection/def.h"
#include "upb/reflection/def.hpp"

class UpbBenchmarkable : public Benchmarkable {
public:
  UpbBenchmarkable() : Benchmarkable() {}

  void serialize() {
    upb_AddressBook *address_book = upb_AddressBook_new(arena_.ptr());
    upb_Person *person = upb_AddressBook_add_people(address_book, arena_.ptr());
    upb_Person_PhoneNumber *pn = upb_Person_add_phones(person, arena_.ptr());

    upb_Person_PhoneNumber_set_number(
        pn, upb_StringView_FromDataAndSize(PERSON_PHONE_NUMBER.data(),
                                           PERSON_PHONE_NUMBER.size()));
    upb_Person_PhoneNumber_set_type(pn, upb_Person_PHONE_TYPE_MOBILE);

    upb_Person_set_email(person, upb_StringView_FromDataAndSize(
                                     PERSON_EMAIL.data(), PERSON_EMAIL.size()));
    upb_Person_set_name(person, upb_StringView_FromDataAndSize(
                                    PERSON_NAME.data(), PERSON_NAME.size()));
    upb_Person_set_id(person, PERSON_ID);

    upb_StringView ser;
    ser.data = upb_AddressBook_serialize(address_book, arena_.ptr(), &ser.size);
  }

  upb::DefPool defpool_;
  upb::Arena arena_;
};
