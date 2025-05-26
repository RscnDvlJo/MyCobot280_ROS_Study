; Auto-generated. Do not edit!


(cl:in-package manual_srvs-srv)


;//! \htmlinclude ManualSrv-request.msg.html

(cl:defclass <ManualSrv-request> (roslisp-msg-protocol:ros-message)
  ((angles
    :reader angles
    :initarg :angles
    :type (cl:vector cl:float)
   :initform (cl:make-array 6 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass ManualSrv-request (<ManualSrv-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ManualSrv-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ManualSrv-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name manual_srvs-srv:<ManualSrv-request> is deprecated: use manual_srvs-srv:ManualSrv-request instead.")))

(cl:ensure-generic-function 'angles-val :lambda-list '(m))
(cl:defmethod angles-val ((m <ManualSrv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader manual_srvs-srv:angles-val is deprecated.  Use manual_srvs-srv:angles instead.")
  (angles m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ManualSrv-request>) ostream)
  "Serializes a message object of type '<ManualSrv-request>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'angles))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ManualSrv-request>) istream)
  "Deserializes a message object of type '<ManualSrv-request>"
  (cl:setf (cl:slot-value msg 'angles) (cl:make-array 6))
  (cl:let ((vals (cl:slot-value msg 'angles)))
    (cl:dotimes (i 6)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ManualSrv-request>)))
  "Returns string type for a service object of type '<ManualSrv-request>"
  "manual_srvs/ManualSrvRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ManualSrv-request)))
  "Returns string type for a service object of type 'ManualSrv-request"
  "manual_srvs/ManualSrvRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ManualSrv-request>)))
  "Returns md5sum for a message object of type '<ManualSrv-request>"
  "cb9460bf78e499f0b8513944c7615a57")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ManualSrv-request)))
  "Returns md5sum for a message object of type 'ManualSrv-request"
  "cb9460bf78e499f0b8513944c7615a57")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ManualSrv-request>)))
  "Returns full string definition for message of type '<ManualSrv-request>"
  (cl:format cl:nil "float64[6] angles~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ManualSrv-request)))
  "Returns full string definition for message of type 'ManualSrv-request"
  (cl:format cl:nil "float64[6] angles~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ManualSrv-request>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'angles) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ManualSrv-request>))
  "Converts a ROS message object to a list"
  (cl:list 'ManualSrv-request
    (cl:cons ':angles (angles msg))
))
;//! \htmlinclude ManualSrv-response.msg.html

(cl:defclass <ManualSrv-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass ManualSrv-response (<ManualSrv-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ManualSrv-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ManualSrv-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name manual_srvs-srv:<ManualSrv-response> is deprecated: use manual_srvs-srv:ManualSrv-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <ManualSrv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader manual_srvs-srv:success-val is deprecated.  Use manual_srvs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ManualSrv-response>) ostream)
  "Serializes a message object of type '<ManualSrv-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ManualSrv-response>) istream)
  "Deserializes a message object of type '<ManualSrv-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ManualSrv-response>)))
  "Returns string type for a service object of type '<ManualSrv-response>"
  "manual_srvs/ManualSrvResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ManualSrv-response)))
  "Returns string type for a service object of type 'ManualSrv-response"
  "manual_srvs/ManualSrvResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ManualSrv-response>)))
  "Returns md5sum for a message object of type '<ManualSrv-response>"
  "cb9460bf78e499f0b8513944c7615a57")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ManualSrv-response)))
  "Returns md5sum for a message object of type 'ManualSrv-response"
  "cb9460bf78e499f0b8513944c7615a57")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ManualSrv-response>)))
  "Returns full string definition for message of type '<ManualSrv-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ManualSrv-response)))
  "Returns full string definition for message of type 'ManualSrv-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ManualSrv-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ManualSrv-response>))
  "Converts a ROS message object to a list"
  (cl:list 'ManualSrv-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'ManualSrv)))
  'ManualSrv-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'ManualSrv)))
  'ManualSrv-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ManualSrv)))
  "Returns string type for a service object of type '<ManualSrv>"
  "manual_srvs/ManualSrv")