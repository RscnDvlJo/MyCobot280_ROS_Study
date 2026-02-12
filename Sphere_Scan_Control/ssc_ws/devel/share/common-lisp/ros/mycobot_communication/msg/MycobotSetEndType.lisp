; Auto-generated. Do not edit!


(cl:in-package mycobot_communication-msg)


;//! \htmlinclude MycobotSetEndType.msg.html

(cl:defclass <MycobotSetEndType> (roslisp-msg-protocol:ros-message)
  ((Status
    :reader Status
    :initarg :Status
    :type cl:fixnum
    :initform 0))
)

(cl:defclass MycobotSetEndType (<MycobotSetEndType>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MycobotSetEndType>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MycobotSetEndType)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mycobot_communication-msg:<MycobotSetEndType> is deprecated: use mycobot_communication-msg:MycobotSetEndType instead.")))

(cl:ensure-generic-function 'Status-val :lambda-list '(m))
(cl:defmethod Status-val ((m <MycobotSetEndType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mycobot_communication-msg:Status-val is deprecated.  Use mycobot_communication-msg:Status instead.")
  (Status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MycobotSetEndType>) ostream)
  "Serializes a message object of type '<MycobotSetEndType>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Status)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MycobotSetEndType>) istream)
  "Deserializes a message object of type '<MycobotSetEndType>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Status)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MycobotSetEndType>)))
  "Returns string type for a message object of type '<MycobotSetEndType>"
  "mycobot_communication/MycobotSetEndType")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MycobotSetEndType)))
  "Returns string type for a message object of type 'MycobotSetEndType"
  "mycobot_communication/MycobotSetEndType")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MycobotSetEndType>)))
  "Returns md5sum for a message object of type '<MycobotSetEndType>"
  "5fa862b628cefe7464ed489433f1bba8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MycobotSetEndType)))
  "Returns md5sum for a message object of type 'MycobotSetEndType"
  "5fa862b628cefe7464ed489433f1bba8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MycobotSetEndType>)))
  "Returns full string definition for message of type '<MycobotSetEndType>"
  (cl:format cl:nil "uint8 Status~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MycobotSetEndType)))
  "Returns full string definition for message of type 'MycobotSetEndType"
  (cl:format cl:nil "uint8 Status~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MycobotSetEndType>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MycobotSetEndType>))
  "Converts a ROS message object to a list"
  (cl:list 'MycobotSetEndType
    (cl:cons ':Status (Status msg))
))
