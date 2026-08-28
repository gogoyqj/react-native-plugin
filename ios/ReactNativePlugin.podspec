require "json"

package = JSON.parse(File.read(File.join(__dir__, "..", "package.json")))

Pod::Spec.new do |s|
  s.name         = "ReactNativePlugin"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.homepage     = package["homepage"]
  s.license      = package["license"]
  s.authors      = package["author"]
  s.source       = { :git => "", :tag => s.version }

  s.platforms    = { :ios => "13.0" }
  s.source_files = "*.{h,mm,cpp}", "../cpp/**/*.{h,cpp}"

  s.dependency "React-Core"
end
