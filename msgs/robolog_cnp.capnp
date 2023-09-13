@0xec754a98fd03ee8f;

using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("robolog_cnp");

enum Robot {
    unknown @0;
    autumn @1;
    betty @2;
    chara @3;
}

struct Metadata {
    robot @0 :Robot;
    gitCommitSha @1 :Text;
    timestamp @2 :UInt64;
}

struct PhysicalState {
    position @0 :Float32;
    velocity @1 :Float32;
    acceleration @2 :Float32;
}

struct Pose3D  {
    x @0 :Float32;
    y @1 :Float32;
    z @2 :Float32;
}

struct RTCycle {
    legStates @0 :List(PhysicalState);
    armState @1 :PhysicalState;
    elbowState @2 :PhysicalState;
    pose @3 :Pose3D;
}

struct Robolog {
    metadata @0 :Metadata;
    cycles @1 :List(RTCycle);
}
