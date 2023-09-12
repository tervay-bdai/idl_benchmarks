#pragma once

#include <iostream>

#include "msgs/address_book_generated.h"
#include "src/benchmark.h"

class FbsBenchmarkable : public Benchmarkable {
public:
  FbsBenchmarkable() : Benchmarkable(), fbs_builder_(1024) {}

  void serialize() {
    flatbuffers::Offset<flatbuffers::String> name =
        fbs_builder_.CreateString("Alice");
    flatbuffers::Offset<flatbuffers::String> email =
        fbs_builder_.CreateString("alice@example.com");
    flatbuffers::Offset<flatbuffers::String> phone_number_str =
        fbs_builder_.CreateString("555-123-1234");

    std::vector<flatbuffers::Offset<PhoneNumber>> phoneNumbers;
    phoneNumbers.emplace_back(
        CreatePhoneNumber(fbs_builder_, phone_number_str,
                          PhoneType::PhoneType_PHONE_TYPE_MOBILE));

    const auto pn = fbs_builder_.CreateVector(phoneNumbers);

    std::vector<flatbuffers::Offset<Person>> people;
    people.emplace_back(CreatePerson(fbs_builder_, name, 1, email, pn));

    const auto ppl = fbs_builder_.CreateVector(people);

    fbs_builder_.Finish(CreateAddressBook(fbs_builder_, ppl));
  }

  flatbuffers::FlatBufferBuilder fbs_builder_;
};
