;; Auto-generated. Do not edit!


(when (boundp 'mycobot_communication::SetEndType)
  (if (not (find-package "MYCOBOT_COMMUNICATION"))
    (make-package "MYCOBOT_COMMUNICATION"))
  (shadow 'SetEndType (find-package "MYCOBOT_COMMUNICATION")))
(unless (find-package "MYCOBOT_COMMUNICATION::SETENDTYPE")
  (make-package "MYCOBOT_COMMUNICATION::SETENDTYPE"))
(unless (find-package "MYCOBOT_COMMUNICATION::SETENDTYPEREQUEST")
  (make-package "MYCOBOT_COMMUNICATION::SETENDTYPEREQUEST"))
(unless (find-package "MYCOBOT_COMMUNICATION::SETENDTYPERESPONSE")
  (make-package "MYCOBOT_COMMUNICATION::SETENDTYPERESPONSE"))

(in-package "ROS")





(defclass mycobot_communication::SetEndTypeRequest
  :super ros::object
  :slots (_Status ))

(defmethod mycobot_communication::SetEndTypeRequest
  (:init
   (&key
    ((:Status __Status) 0)
    )
   (send-super :init)
   (setq _Status (round __Status))
   self)
  (:Status
   (&optional __Status)
   (if __Status (setq _Status __Status)) _Status)
  (:serialization-length
   ()
   (+
    ;; uint8 _Status
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _Status
       (write-byte _Status s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _Status
     (setq _Status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(defclass mycobot_communication::SetEndTypeResponse
  :super ros::object
  :slots (_Flag ))

(defmethod mycobot_communication::SetEndTypeResponse
  (:init
   (&key
    ((:Flag __Flag) nil)
    )
   (send-super :init)
   (setq _Flag __Flag)
   self)
  (:Flag
   (&optional (__Flag :null))
   (if (not (eq __Flag :null)) (setq _Flag __Flag)) _Flag)
  (:serialization-length
   ()
   (+
    ;; bool _Flag
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _Flag
       (if _Flag (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _Flag
     (setq _Flag (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass mycobot_communication::SetEndType
  :super ros::object
  :slots ())

(setf (get mycobot_communication::SetEndType :md5sum-) "9dfdf50aef7688b8c7d43efb64190a81")
(setf (get mycobot_communication::SetEndType :datatype-) "mycobot_communication/SetEndType")
(setf (get mycobot_communication::SetEndType :request) mycobot_communication::SetEndTypeRequest)
(setf (get mycobot_communication::SetEndType :response) mycobot_communication::SetEndTypeResponse)

(defmethod mycobot_communication::SetEndTypeRequest
  (:response () (instance mycobot_communication::SetEndTypeResponse :init)))

(setf (get mycobot_communication::SetEndTypeRequest :md5sum-) "9dfdf50aef7688b8c7d43efb64190a81")
(setf (get mycobot_communication::SetEndTypeRequest :datatype-) "mycobot_communication/SetEndTypeRequest")
(setf (get mycobot_communication::SetEndTypeRequest :definition-)
      "uint8 Status

---

bool Flag
")

(setf (get mycobot_communication::SetEndTypeResponse :md5sum-) "9dfdf50aef7688b8c7d43efb64190a81")
(setf (get mycobot_communication::SetEndTypeResponse :datatype-) "mycobot_communication/SetEndTypeResponse")
(setf (get mycobot_communication::SetEndTypeResponse :definition-)
      "uint8 Status

---

bool Flag
")



(provide :mycobot_communication/SetEndType "9dfdf50aef7688b8c7d43efb64190a81")


