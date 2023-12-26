File.open('randoms', 'w') do |f|
  20.times do
    f.write("#{rand(10)} ")
  end
end
