# frozen_string_literal: true

RSpec.describe Framegrabber do
  it "has a version number" do
    expect(Framegrabber::VERSION).not_to be nil
  end

  it "has version 0.1.0" do
    expect(Framegrabber::VERSION).to eq("0.1.0")
  end

  it "responds to open method" do
    expect(Framegrabber).to respond_to(:open)
  end

  it "responds to grab_frame method" do
    expect(Framegrabber).to respond_to(:grab_frame)
  end

  it "responds to release method" do
    expect(Framegrabber).to respond_to(:release)
  end

  it "defines grab_image method when RMagick is available" do
    if defined?(Magick)
      expect(Framegrabber).to respond_to(:grab_image)
    else
      expect(Framegrabber).not_to respond_to(:grab_image)
    end
  end
end
