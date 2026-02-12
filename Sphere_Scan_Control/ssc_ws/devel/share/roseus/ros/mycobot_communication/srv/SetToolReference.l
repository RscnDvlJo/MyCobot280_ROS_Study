;; Auto-generated. Do not edit!


(when (boundp 'mycobot_communication::SetToolReference)
  (if (not (find-package "MYCOBOT_COMMUNICATION"))
    (make-package "MYCOBOT_COMMUNICATION"))
  (shadow 'SetToolReference (find-package "MYCOBOT_COMMUNICATION")))
(unless (find-package "MYCOBOT_COMMUNICATION::SETTOOLREFERENCE")
  (make-package "MYCOBOT_COMMUNICATION::SETTOOLREFERENCE"))
(unless (find-package "MYCOBOT_COMMUNICATION::SETTOOLREFERENCEREQUEST")
  (make-package "MYCOBOT_COMMUNICATION::SETTOOLREFERENCEREQUEST"))
(unless (find-package "MYCOBOT_COMMUNICATION::SETTOOLREFERENCERESPONSE")
  (make-package "MYCOBOT_COMMUNICATION::SETTOOLREFERENCERESPONSE"))

(in-package "ROS")





(defclass mycobot_communication::SetToolReferenceRequest
  :super ros::object
  :slots (_x _y _z _rx _ry _rz ))

(defmethod mycobot_communication::SetToolReferenceRequest
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:rx __rx) 0.0)
    ((:ry __ry) 0.0)
    ((:rz __rz) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _rx (float __rx))
   (setq _ry (float __ry))
   (setq _rz (float __rz))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:rx
   (&optional __rx)
   (if __rx (setq _rx __rx)) _rx)
  (:ry
   (&optional __ry)
   (if __ry (setq _ry __ry)) _ry)
  (:rz
   (&optional __rz)
   (if __rz (setq _rz __rz)) _rz)
  (:serialization-length
   ()
   (+
    ;; float32 _x
    4
    ;; float32 _y
    4
    ;; float32 _z
    4
    ;; float32 _rx
    4
    ;; float32 _ry
    4
    ;; float32 _rz
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _z
       (sys::poke _z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rx
       (sys::poke _rx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ry
       (sys::poke _ry (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rz
       (sys::poke _rz (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _z
     (setq _z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rx
     (setq _rx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ry
     (setq _ry (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rz
     (setq _rz (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass mycobot_communication::SetToolReferenceResponse
  :super ros::object
  :slots (_Flag ))

(defmethod mycobot_communication::SetToolReferenceResponse
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

(defclass mycobot_communication::SetToolReference
  :super ros::object
  :slots ())

(setf (get mycobot_communication::SetToolReference :md5sum-) "eed7ebf6b157baae92879470642b26d9")
(setf (get mycobot_communication::SetToolReference :datatype-) "mycobot_communication/SetToolReference")
(setf (get mycobot_communication::SetToolReference :request) mycobot_communication::SetToolReferenceRequest)
(setf (get mycobot_communication::SetToolReference :response) mycobot_communication::SetToolReferenceResponse)

(defmethod mycobot_communication::SetToolReferenceRequest
  (:response () (instance mycobot_communication::SetToolReferenceResponse :init)))

(setf (get mycobot_communication::SetToolReferenceRequest :md5sum-) "eed7ebf6b157baae92879470642b26d9")
(setf (get mycobot_communication::SetToolReferenceRequest :datatype-) "mycobot_communication/SetToolReferenceRequest")
(setf (get mycobot_communication::SetToolReferenceRequest :definition-)
      "float32 x
float32 y
float32 z
float32 rx
float32 ry
float32 rz

---

bool Flag
")

(setf (get mycobot_communication::SetToolReferenceResponse :md5sum-) "eed7ebf6b157baae92879470642b26d9")
(setf (get mycobot_communication::SetToolReferenceResponse :datatype-) "mycobot_communication/SetToolReferenceResponse")
(setf (get mycobot_communication::SetToolReferenceResponse :definition-)
      "float32 x
float32 y
float32 z
float32 rx
float32 ry
float32 rz

---

bool Flag
")



(provide :mycobot_communication/SetToolReference "eed7ebf6b157baae92879470642b26d9")


