# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: _py_px4_position_setpoint_triplet.proto

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
  name='_py_px4_position_setpoint_triplet.proto',
  package='',
  serialized_pb=_b('\n\'_py_px4_position_setpoint_triplet.proto\"\xa1\x04\n\x18px4_position_setpoint_pb\x12\x1b\n\x13\x41\x63\x63\x65lerationIsForce\x18\x01 \x02(\x08\x12\x1b\n\x13\x44isableMcYawControl\x18\x02 \x02(\x08\x12\x0b\n\x03Yaw\x18\x03 \x02(\x02\x12\x0b\n\x03Lon\x18\x04 \x02(\x01\x12\x10\n\x08PitchMin\x18\x05 \x02(\x02\x12\n\n\x02VX\x18\x06 \x02(\x02\x12\r\n\x05Valid\x18\x07 \x02(\x08\x12\x10\n\x08YawValid\x18\x08 \x02(\x08\x12\t\n\x01X\x18\t \x02(\x02\x12\x15\n\rPositionValid\x18\n \x02(\x08\x12\x10\n\x08Yawspeed\x18\x0b \x02(\x02\x12\x15\n\rVelocityValid\x18\x0c \x02(\x08\x12\x0c\n\x04Type\x18\r \x02(\r\x12\t\n\x01Z\x18\x0e \x02(\x02\x12\x18\n\x10\x43ruisingThrottle\x18\x0f \x02(\x02\x12\x0b\n\x03Lat\x18\x10 \x02(\x01\x12\x15\n\rYawspeedValid\x18\x11 \x02(\x08\x12\x15\n\rCruisingSpeed\x18\x12 \x02(\x02\x12\x17\n\x0fLoiterDirection\x18\x13 \x02(\x05\x12\x0b\n\x03\x41_Z\x18\x14 \x02(\x02\x12\x0b\n\x03\x41_Y\x18\x15 \x02(\x02\x12\x0b\n\x03\x41_X\x18\x16 \x02(\x02\x12\t\n\x01Y\x18\x17 \x02(\x02\x12\n\n\x02VY\x18\x18 \x02(\x02\x12\n\n\x02VZ\x18\x19 \x02(\x02\x12\x18\n\x10\x41\x63\x63\x65ptanceRadius\x18\x1a \x02(\x02\x12\x19\n\x11\x41\x63\x63\x65lerationValid\x18\x1b \x02(\x08\x12\x14\n\x0cLoiterRadius\x18\x1c \x02(\x02\x12\x0b\n\x03\x41lt\x18\x1d \x02(\x02\"\xb7\x01\n px4_position_setpoint_triplet_pb\x12*\n\x07\x43urrent\x18\x01 \x02(\x0b\x32\x19.px4_position_setpoint_pb\x12\x11\n\tTimestamp\x18\x02 \x02(\x04\x12\'\n\x04Next\x18\x03 \x02(\x0b\x32\x19.px4_position_setpoint_pb\x12+\n\x08Previous\x18\x04 \x02(\x0b\x32\x19.px4_position_setpoint_pb')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_PX4_POSITION_SETPOINT_PB = _descriptor.Descriptor(
  name='px4_position_setpoint_pb',
  full_name='px4_position_setpoint_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='AccelerationIsForce', full_name='px4_position_setpoint_pb.AccelerationIsForce', index=0,
      number=1, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='DisableMcYawControl', full_name='px4_position_setpoint_pb.DisableMcYawControl', index=1,
      number=2, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Yaw', full_name='px4_position_setpoint_pb.Yaw', index=2,
      number=3, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Lon', full_name='px4_position_setpoint_pb.Lon', index=3,
      number=4, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='PitchMin', full_name='px4_position_setpoint_pb.PitchMin', index=4,
      number=5, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='VX', full_name='px4_position_setpoint_pb.VX', index=5,
      number=6, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Valid', full_name='px4_position_setpoint_pb.Valid', index=6,
      number=7, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='YawValid', full_name='px4_position_setpoint_pb.YawValid', index=7,
      number=8, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='X', full_name='px4_position_setpoint_pb.X', index=8,
      number=9, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='PositionValid', full_name='px4_position_setpoint_pb.PositionValid', index=9,
      number=10, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Yawspeed', full_name='px4_position_setpoint_pb.Yawspeed', index=10,
      number=11, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='VelocityValid', full_name='px4_position_setpoint_pb.VelocityValid', index=11,
      number=12, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Type', full_name='px4_position_setpoint_pb.Type', index=12,
      number=13, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Z', full_name='px4_position_setpoint_pb.Z', index=13,
      number=14, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='CruisingThrottle', full_name='px4_position_setpoint_pb.CruisingThrottle', index=14,
      number=15, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Lat', full_name='px4_position_setpoint_pb.Lat', index=15,
      number=16, type=1, cpp_type=5, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='YawspeedValid', full_name='px4_position_setpoint_pb.YawspeedValid', index=16,
      number=17, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='CruisingSpeed', full_name='px4_position_setpoint_pb.CruisingSpeed', index=17,
      number=18, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='LoiterDirection', full_name='px4_position_setpoint_pb.LoiterDirection', index=18,
      number=19, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='A_Z', full_name='px4_position_setpoint_pb.A_Z', index=19,
      number=20, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='A_Y', full_name='px4_position_setpoint_pb.A_Y', index=20,
      number=21, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='A_X', full_name='px4_position_setpoint_pb.A_X', index=21,
      number=22, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Y', full_name='px4_position_setpoint_pb.Y', index=22,
      number=23, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='VY', full_name='px4_position_setpoint_pb.VY', index=23,
      number=24, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='VZ', full_name='px4_position_setpoint_pb.VZ', index=24,
      number=25, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='AcceptanceRadius', full_name='px4_position_setpoint_pb.AcceptanceRadius', index=25,
      number=26, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='AccelerationValid', full_name='px4_position_setpoint_pb.AccelerationValid', index=26,
      number=27, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='LoiterRadius', full_name='px4_position_setpoint_pb.LoiterRadius', index=27,
      number=28, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Alt', full_name='px4_position_setpoint_pb.Alt', index=28,
      number=29, type=2, cpp_type=6, label=2,
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
  serialized_start=44,
  serialized_end=589,
)


_PX4_POSITION_SETPOINT_TRIPLET_PB = _descriptor.Descriptor(
  name='px4_position_setpoint_triplet_pb',
  full_name='px4_position_setpoint_triplet_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='Current', full_name='px4_position_setpoint_triplet_pb.Current', index=0,
      number=1, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Timestamp', full_name='px4_position_setpoint_triplet_pb.Timestamp', index=1,
      number=2, type=4, cpp_type=4, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Next', full_name='px4_position_setpoint_triplet_pb.Next', index=2,
      number=3, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Previous', full_name='px4_position_setpoint_triplet_pb.Previous', index=3,
      number=4, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
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
  serialized_start=592,
  serialized_end=775,
)

_PX4_POSITION_SETPOINT_TRIPLET_PB.fields_by_name['Current'].message_type = _PX4_POSITION_SETPOINT_PB
_PX4_POSITION_SETPOINT_TRIPLET_PB.fields_by_name['Next'].message_type = _PX4_POSITION_SETPOINT_PB
_PX4_POSITION_SETPOINT_TRIPLET_PB.fields_by_name['Previous'].message_type = _PX4_POSITION_SETPOINT_PB
DESCRIPTOR.message_types_by_name['px4_position_setpoint_pb'] = _PX4_POSITION_SETPOINT_PB
DESCRIPTOR.message_types_by_name['px4_position_setpoint_triplet_pb'] = _PX4_POSITION_SETPOINT_TRIPLET_PB

px4_position_setpoint_pb = _reflection.GeneratedProtocolMessageType('px4_position_setpoint_pb', (_message.Message,), dict(
  DESCRIPTOR = _PX4_POSITION_SETPOINT_PB,
  __module__ = '_py_px4_position_setpoint_triplet_pb2'
  # @@protoc_insertion_point(class_scope:px4_position_setpoint_pb)
  ))
_sym_db.RegisterMessage(px4_position_setpoint_pb)

px4_position_setpoint_triplet_pb = _reflection.GeneratedProtocolMessageType('px4_position_setpoint_triplet_pb', (_message.Message,), dict(
  DESCRIPTOR = _PX4_POSITION_SETPOINT_TRIPLET_PB,
  __module__ = '_py_px4_position_setpoint_triplet_pb2'
  # @@protoc_insertion_point(class_scope:px4_position_setpoint_triplet_pb)
  ))
_sym_db.RegisterMessage(px4_position_setpoint_triplet_pb)


# @@protoc_insertion_point(module_scope)
