# frozen_string_literal: true

require_relative 'framegrabber/version'
require 'grab_frame_ext'
begin
  require 'rmagick'
rescue LoadError
end

module Framegrabber
  if const_defined?('Magick')
    def self.grab_image
      # Discard first frame (original hack to ensure camera is ready)
      grab_frame
      frame = grab_frame

      # Use system ImageMagick to convert raw RGB data to image
      require 'tempfile'
      Tempfile.open(['framegrabber', '.rgb']) do |temp_rgb|
        temp_rgb.binmode
        temp_rgb.write(frame.flatten.pack('C*'))
        temp_rgb.close

        Tempfile.open(['framegrabber', '.png']) do |temp_png|
          temp_png.close

          # Convert RGB data to PNG using ImageMagick
          system('magick', '-size', "#{frame.first.size}x#{frame.size}",
                 '-depth', '8', "rgb:#{temp_rgb.path}", temp_png.path)

          # Read the PNG with RMagick
          img = Magick::Image.read(temp_png.path).first
          return img
        end
      end
    end
  end
end
