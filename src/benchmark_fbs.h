#pragma once

#include <iostream>

#include "msgs/address_book_generated.h"
#include "src/benchmark.h"
#include "src/consts.h"

class FbsBenchmarkable : public Benchmarkable {
public:
  FbsBenchmarkable() : Benchmarkable(), fbs_builder_(1024) {}

  void serialize() {
    flatbuffers::Offset<flatbuffers::String> name =
        fbs_builder_.CreateString(PERSON_NAME);
    flatbuffers::Offset<flatbuffers::String> email =
        fbs_builder_.CreateString(PERSON_EMAIL);
    flatbuffers::Offset<flatbuffers::String> phone_number_str =
        fbs_builder_.CreateString(PERSON_EMAIL);

    std::vector<flatbuffers::Offset<fbs::PhoneNumber>> phoneNumbers;
    phoneNumbers.emplace_back(
        CreatePhoneNumber(fbs_builder_, phone_number_str,
                          fbs::PhoneType::PhoneType_PHONE_TYPE_MOBILE));

    const auto pn = fbs_builder_.CreateVector(phoneNumbers);

    std::vector<flatbuffers::Offset<fbs::Person>> people;
    people.emplace_back(
        fbs::CreatePerson(fbs_builder_, name, PERSON_ID, email, pn));

    const auto ppl = fbs_builder_.CreateVector(people);

    fbs_builder_.Finish(fbs::CreateAddressBook(fbs_builder_, ppl));
  }

  flatbuffers::FlatBufferBuilder fbs_builder_;
};
