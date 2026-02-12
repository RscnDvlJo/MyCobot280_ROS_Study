;; Auto-generated. Do not edit!


(when (boundp 'mycobot_communication::SetFreshMode)
  (if (not (find-package "MYCOBOT_COMMUNICATION"))
    (make-package "MYCOBOT_COMMUNICATION"))
  (shadow 'SetFreshMode (find-package "MYCOBOT_COMMUNICATION")))
(unless (find-package "MYCOBOT_COMMUNICATION::SETFRESHMODE")
  (make-package "MYCOBOT_COMMUNICATION::SETFRESHMODE"))
(unless (find-package "MYCOBOT_COMMUNICATION::SETFRESHMODEREQUEST")
  (make-package "MYCOBOT_COMMUNICATION::SETFRESHMODEREQUEST"))
(unless (find-package "MYCOBOT_COMMUNICATION::SETFRESHMODERESPONSE")
  (make-package "MYCOBOT_COMMUNICATION::SETFRESHMODERESPONSE"))

(in-package "ROS")





(defclass mycobot_communication::SetFreshModeRequest
  :super ros::object
  :slots (_Status ))

(defmethod mycobot_communication::SetFreshModeRequest
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

(defclass mycobot_communication::SetFreshModeResponse
  :super ros::object
  :slots (_Flag ))

(defmethod mycobot_communication::SetFreshModeResponse
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

(defclass mycobot_communication::SetFreshMode
  :super ros::object
  :slots ())

(setf (get mycobot_communication::SetFreshMode :md5sum-) "9dfdf50aef7688b8c7d43efb64190a81")
(setf (get mycobot_communication::SetFreshMode :datatype-) "mycobot_communication/SetFreshMode")
(setf (get mycobot_communication::SetFreshMode :request) mycobot_communication::SetFreshModeRequest)
(setf (get mycobot_communication::SetFreshMode :response) mycobot_communication::SetFreshModeResponse)

(defmethod mycobot_communication::SetFreshModeRequest
  (:response () (instance mycobot_communication::SetFreshModeResponse :init)))

(setf (get mycobot_communication::SetFreshModeRequest :md5sum-) "9dfdf50aef7688b8c7d43efb64190a81")
(setf (get mycobot_communication::SetFreshModeRequest :datatype-) "mycobot_communication/SetFreshModeRequest")
(setf (get mycobot_communication::SetFreshModeRequest :definition-)
      "uint8 Status

---

bool Flag
")

(setf (get mycobot_communication::SetFreshModeResponse :md5sum-) "9dfdf50aef7688b8c7d43efb64190a81")
(setf (get mycobot_communication::SetFreshModeResponse :datatype-) "mycobot_communication/SetFreshModeResponse")
(setf (get mycobot_communication::SetFreshModeResponse :definition-)
      "uint8 Status

---

bool Flag
")



(provide :mycobot_communication/SetFreshMode "9dfdf50aef7688b8c7d43efb64190a81")


