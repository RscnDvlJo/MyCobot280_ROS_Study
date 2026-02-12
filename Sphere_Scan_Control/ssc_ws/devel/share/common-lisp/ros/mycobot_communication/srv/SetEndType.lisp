; Auto-generated. Do not edit!


(cl:in-package mycobot_communication-srv)


;//! \htmlinclude SetEndType-request.msg.html

(cl:defclass <SetEndType-request> (roslisp-msg-protocol:ros-message)
  ((Status
    :reader Status
    :initarg :Status
    :type cl:fixnum
    :initform 0))
)

(cl:defclass SetEndType-request (<SetEndType-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetEndType-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetEndType-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mycobot_communication-srv:<SetEndType-request> is deprecated: use mycobot_communication-srv:SetEndType-request instead.")))

(cl:ensure-generic-function 'Status-val :lambda-list '(m))
(cl:defmethod Status-val ((m <SetEndType-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mycobot_communication-srv:Status-val is deprecated.  Use mycobot_communication-srv:Status instead.")
  (Status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetEndType-request>) ostream)
  "Serializes a message object of type '<SetEndType-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Status)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetEndType-request>) istream)
  "Deserializes a message object of type '<SetEndType-request>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'Status)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetEndType-request>)))
  "Returns string type for a service object of type '<SetEndType-request>"
  "mycobot_communication/SetEndTypeRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetEndType-request)))
  "Returns string type for a service object of type 'SetEndType-request"
  "mycobot_communication/SetEndTypeRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetEndType-request>)))
  "Returns md5sum for a message object of type '<SetEndType-request>"
  "9dfdf50aef7688b8c7d43efb64190a81")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetEndType-request)))
  "Returns md5sum for a message object of type 'SetEndType-request"
  "9dfdf50aef7688b8c7d43efb64190a81")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetEndType-request>)))
  "Returns full string definition for message of type '<SetEndType-request>"
  (cl:format cl:nil "uint8 Status~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetEndType-request)))
  "Returns full string definition for message of type 'SetEndType-request"
  (cl:format cl:nil "uint8 Status~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetEndType-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetEndType-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetEndType-request
    (cl:cons ':Status (Status msg))
))
;//! \htmlinclude SetEndType-response.msg.html

(cl:defclass <SetEndType-response> (roslisp-msg-protocol:ros-message)
  ((Flag
    :reader Flag
    :initarg :Flag
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetEndType-response (<SetEndType-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetEndType-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetEndType-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mycobot_communication-srv:<SetEndType-response> is deprecated: use mycobot_communication-srv:SetEndType-response instead.")))

(cl:ensure-generic-function 'Flag-val :lambda-list '(m))
(cl:defmethod Flag-val ((m <SetEndType-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mycobot_communication-srv:Flag-val is deprecated.  Use mycobot_communication-srv:Flag instead.")
  (Flag m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetEndType-response>) ostream)
  "Serializes a message object of type '<SetEndType-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'Flag) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetEndType-response>) istream)
  "Deserializes a message object of type '<SetEndType-response>"
    (cl:setf (cl:slot-value msg 'Flag) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetEndType-response>)))
  "Returns string type for a service object of type '<SetEndType-response>"
  "mycobot_communication/SetEndTypeResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetEndType-response)))
  "Returns string type for a service object of type 'SetEndType-response"
  "mycobot_communication/SetEndTypeResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetEndType-response>)))
  "Returns md5sum for a message object of type '<SetEndType-response>"
  "9dfdf50aef7688b8c7d43efb64190a81")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetEndType-response)))
  "Returns md5sum for a message object of type 'SetEndType-response"
  "9dfdf50aef7688b8c7d43efb64190a81")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetEndType-response>)))
  "Returns full string definition for message of type '<SetEndType-response>"
  (cl:format cl:nil "~%bool Flag~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetEndType-response)))
  "Returns full string definition for message of type 'SetEndType-response"
  (cl:format cl:nil "~%bool Flag~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetEndType-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetEndType-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetEndType-response
    (cl:cons ':Flag (Flag msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetEndType)))
  'SetEndType-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetEndType)))
  'SetEndType-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetEndType)))
  "Returns string type for a service object of type '<SetEndType>"
  "mycobot_communication/SetEndType")