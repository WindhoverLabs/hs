# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: _py_PX4_VehicleStatusMsg_t.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='_py_PX4_VehicleStatusMsg_t.proto',
  package='',
  serialized_pb=_b('\n _py_PX4_VehicleStatusMsg_t.proto\"\xbc\x04\n\x19PX4_VehicleStatusMsg_t_pb\x12\x16\n\x0eMissionFailure\x18\x01 \x02(\x08\x12\x10\n\x08\x46\x61ilsafe\x18\x02 \x02(\x08\x12\x10\n\x08HilState\x18\x03 \x02(\r\x12\x1b\n\x13VtolFwPermanentStab\x18\x04 \x02(\x08\x12\x13\n\x0b\x41rmingState\x18\x05 \x02(\r\x12\x18\n\x10\x45ngineFailureCmd\x18\x06 \x02(\x08\x12\x10\n\x08NavState\x18\x07 \x02(\r\x12$\n\x1cOnboardControlSensorsPresent\x18\x08 \x02(\r\x12\x1b\n\x13\x44\x61taLinkLostCounter\x18\t \x02(\r\x12\x11\n\tTlmHeader\x18\n \x03(\r\x12\x10\n\x08SystemID\x18\x0b \x02(\r\x12$\n\x1cOnboardControlSensorsEnabled\x18\x0c \x02(\r\x12\x15\n\rEngineFailure\x18\r \x02(\x08\x12\x18\n\x10InTransitionMode\x18\x0e \x02(\x08\x12\x14\n\x0cRcSignalLost\x18\x0f \x02(\x08\x12\x0e\n\x06IsVtol\x18\x10 \x02(\x08\x12\x14\n\x0cIsRotaryWing\x18\x11 \x02(\x08\x12\x14\n\x0c\x44\x61taLinkLost\x18\x12 \x02(\x08\x12\x12\n\nSystemType\x18\x13 \x02(\r\x12\x11\n\tTimestamp\x18\x14 \x02(\x04\x12#\n\x1bOnboardControlSensorsHealth\x18\x15 \x02(\r\x12\x13\n\x0b\x43omponentID\x18\x16 \x02(\r\x12\x13\n\x0bRcInputMode\x18\x17 \x02(\r')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_PX4_VEHICLESTATUSMSG_T_PB = _descriptor.Descriptor(
  name='PX4_VehicleStatusMsg_t_pb',
  full_name='PX4_VehicleStatusMsg_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='MissionFailure', full_name='PX4_VehicleStatusMsg_t_pb.MissionFailure', index=0,
      number=1, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Failsafe', full_name='PX4_VehicleStatusMsg_t_pb.Failsafe', index=1,
      number=2, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='HilState', full_name='PX4_VehicleStatusMsg_t_pb.HilState', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='VtolFwPermanentStab', full_name='PX4_VehicleStatusMsg_t_pb.VtolFwPermanentStab', index=3,
      number=4, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ArmingState', full_name='PX4_VehicleStatusMsg_t_pb.ArmingState', index=4,
      number=5, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='EngineFailureCmd', full_name='PX4_VehicleStatusMsg_t_pb.EngineFailureCmd', index=5,
      number=6, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='NavState', full_name='PX4_VehicleStatusMsg_t_pb.NavState', index=6,
      number=7, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='OnboardControlSensorsPresent', full_name='PX4_VehicleStatusMsg_t_pb.OnboardControlSensorsPresent', index=7,
      number=8, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='DataLinkLostCounter', full_name='PX4_VehicleStatusMsg_t_pb.DataLinkLostCounter', index=8,
      number=9, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='TlmHeader', full_name='PX4_VehicleStatusMsg_t_pb.TlmHeader', index=9,
      number=10, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='SystemID', full_name='PX4_VehicleStatusMsg_t_pb.SystemID', index=10,
      number=11, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='OnboardControlSensorsEnabled', full_name='PX4_VehicleStatusMsg_t_pb.OnboardControlSensorsEnabled', index=11,
      number=12, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='EngineFailure', full_name='PX4_VehicleStatusMsg_t_pb.EngineFailure', index=12,
      number=13, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='InTransitionMode', full_name='PX4_VehicleStatusMsg_t_pb.InTransitionMode', index=13,
      number=14, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='RcSignalLost', full_name='PX4_VehicleStatusMsg_t_pb.RcSignalLost', index=14,
      number=15, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='IsVtol', full_name='PX4_VehicleStatusMsg_t_pb.IsVtol', index=15,
      number=16, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='IsRotaryWing', full_name='PX4_VehicleStatusMsg_t_pb.IsRotaryWing', index=16,
      number=17, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='DataLinkLost', full_name='PX4_VehicleStatusMsg_t_pb.DataLinkLost', index=17,
      number=18, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='SystemType', full_name='PX4_VehicleStatusMsg_t_pb.SystemType', index=18,
      number=19, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Timestamp', full_name='PX4_VehicleStatusMsg_t_pb.Timestamp', index=19,
      number=20, type=4, cpp_type=4, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='OnboardControlSensorsHealth', full_name='PX4_VehicleStatusMsg_t_pb.OnboardControlSensorsHealth', index=20,
      number=21, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ComponentID', full_name='PX4_VehicleStatusMsg_t_pb.ComponentID', index=21,
      number=22, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='RcInputMode', full_name='PX4_VehicleStatusMsg_t_pb.RcInputMode', index=22,
      number=23, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=37,
  serialized_end=609,
)

DESCRIPTOR.message_types_by_name['PX4_VehicleStatusMsg_t_pb'] = _PX4_VEHICLESTATUSMSG_T_PB

PX4_VehicleStatusMsg_t_pb = _reflection.GeneratedProtocolMessageType('PX4_VehicleStatusMsg_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _PX4_VEHICLESTATUSMSG_T_PB,
  __module__ = '_py_PX4_VehicleStatusMsg_t_pb2'
  # @@protoc_insertion_point(class_scope:PX4_VehicleStatusMsg_t_pb)
  ))
_sym_db.RegisterMessage(PX4_VehicleStatusMsg_t_pb)


# @@protoc_insertion_point(module_scope)
