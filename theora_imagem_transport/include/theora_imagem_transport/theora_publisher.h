#ifndef IMAGEM_TRANSPORT_THEORA_PUBLISHER_H
#define IMAGEM_TRANSPORT_THEORA_PUBLISHER_H

#include <message_transport/simple_publisher_plugin.h>
#include <sensor_msgs/Image.h>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <cv_bridge/CvBridge.h>
#include <theora_imagem_transport/packet.h>

#include <theora/codec.h>
#include <theora/theoraenc.h>
#include <theora/theoradec.h>

namespace theora_imagem_transport {

class TheoraPublisher : public message_transport::SimplePublisherPlugin<sensor_msgs::Image,theora_imagem_transport::packet>
{
public:
  TheoraPublisher();
  virtual ~TheoraPublisher();

  //Return the system unique string representing the theora transport type
  virtual std::string getTransportName() const
  {
    return "theora";
  }

protected:
  //Callback to send header packets to new clients
  virtual void connectCallback(const ros::SingleSubscriberPublisher& pub);

  //Main publish function
  virtual void publish(const sensor_msgs::Image& message,
		  const message_transport::SimplePublisherPlugin<sensor_msgs::Image,theora_imagem_transport::packet>::PublishFn& publish_fn) const ;

private:
  //Utility functions
  void sendHeader(const ros::SingleSubscriberPublisher& pub) const;
  void ensure_encoding_context(const CvSize &size, const PublishFn& publish_fn) const;
  void oggPacketToMsg(const ogg_packet &oggpacket, theora_imagem_transport::packet &msgOutput) const;

  //I have some reservations about making everything mutable like this but
  //from the users perspective the publisher is essentially stateless except for differences in
  //bitrate of the resulting stream and required image format.  Thus in order to match the
  //ros API in image_publisher the publish method is still const

  mutable sensor_msgs::CvBridge img_bridge_;
  mutable th_enc_ctx* encoding_context_;
  mutable std::vector<ogg_packet> stream_header_;

  //Offsets to make image size into multiple of 16 (with alignment of image data to even pixels I believe)
  mutable int nearestWidth;
  mutable int nearestHeight;
  mutable int nearestXoff;
  mutable int nearestYoff;
};

} //namespace compressed_image_transport

#endif // IMAGEM_TRANSPORT_THEORA_PUBLISHER_H
