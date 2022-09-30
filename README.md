# Framegrabber

This gem uses OpenCV to grab an image from a camera. 

It's meant to replace a dozen of difficult to execute setups 
for grabbing images and uses much newer OpenCV than [ruby-opencv](https://github.com/ruby-opencv/ruby-opencv).

## Prerequisites

Framegrabber relies only on OpenCV, however it can use [RMagick's](https://github.com/rmagick/rmagick) 
Image format if it is included, which in turn uses ImageMagick.

#### OpenCV

macOS:

```
$ brew install opencv
```

Ubuntu/Debian:

```
$ sudo apt install libopencv-dev
```

It should work with other *nix systems if OpenCV is available.

## Installation

Install the gem and add to the application's Gemfile by executing:

    $ bundle add framegrabber

If bundler is not being used to manage dependencies, install the gem by executing:

    $ gem install framegrabber

## Usage

```ruby
def grab_a_nice_image
  # Open a camera, camera ids are numbered starting with 0.
  # We support only one camera at a time.
  # You can call this now and grab multiple frames 
  # before you close it.
  Framegrabber.open(0)

  # Array of arrays of RGB values for pixels
  @rgb = Framegrabber.grab_frame

  # RMagick's Image object
  @image = Framegrabber.grab_image

rescue RuntimeError => e
  
  # Camera may be unavailable or frame might be empty
  # At this point we don't have nice error handling
  puts "Oh no! #{e.message}"
ensure
  
  # Camera will stay active until it is released
  Framegrabber.release 
end
```

## Development

Clone this repo, run `bundle` and `rake compile`. 

Use `bin/console` to poke around and see what you can improve.

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/khasinski/framegrabber. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [code of conduct](https://github.com/[USERNAME]/framegrabber/blob/master/CODE_OF_CONDUCT.md).

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the Framegrabber project's codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/khasinski/framegrabber/blob/master/CODE_OF_CONDUCT.md).
